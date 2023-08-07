import abc
from math import ceil
from scipy.stats import beta
from sympy import symbols, solve

from smc.smc_engine.property_specification import BaseSpecification
from smc.smc_engine.data_generator import DataGeneratorException


class ModelChecker(abc.ABC):
    def __init__(self, model: BaseSpecification):
        assert isinstance(model, BaseSpecification)
        self.model: BaseSpecification = model

    @abc.abstractmethod
    def verify(self):
        """Run the algorithm. Because the Checker is given the model, it may use the model.check_sample_satisfy()
        function to get a boolean value on whether the samples satisfy the property
        """
        pass


class HPSTLAlgorithm(ModelChecker):
    """Algorithm 1 from https://arxiv.org/abs/1906.07253
    https://github.com/Mojzaar/Benchmarks/blob/master/Powertrain/HPSTL.m"""

    # TODO: this is late to put in information, put it somewhere else instead?
    def verify(self, prob_threshold: float, desired_conf: float, continuous: bool = False):
        """
        :param prob_threshold: probability threshold. As in: the proportion of samples that satisfy the property.
         e.g. 0.95 means that 95% of the samples are faster than the hypothesis
        :param desired_conf: desired confidence level
        """
        a_result = None  # algorithm result. a_result value of None suggests no convergence
        num_trials = 0  # number of trials
        satisfied_trials = 0  # number of trials satisfying condition
        conf_cp = 0  # initial confidence level (clopper-pearson)
        conf_cp_list = []  # list of confidence level at each iteration
        lean_list = []  # list of where the algorithm is leaning at every iteration before converging

        while (conf_cp < desired_conf) or continuous:  # loop until confidence level is reached
            try:
                if self.model.check_sample_satisfy():
                    satisfied_trials += 1
                # Increase num_trials after checking for more samples, in case of a GetterException
                num_trials += 1
                # Compute the new significance level
                if satisfied_trials / num_trials < prob_threshold:
                    a, b = (0, prob_threshold)
                else:
                    a, b = (prob_threshold, 1)

                # Calculate the new confidence
                if satisfied_trials == 0:
                    conf_cp = pow(1 - a, num_trials) - pow(1 - b, num_trials)
                elif satisfied_trials == num_trials:
                    conf_cp = pow(b, num_trials) - pow(a, num_trials)
                else:
                    dist_a = beta.cdf(b, satisfied_trials + 1, num_trials - satisfied_trials)
                    dist_b = beta.cdf(a, satisfied_trials, num_trials - satisfied_trials + 1)
                    conf_cp = dist_a - dist_b
                conf_cp_list.append(conf_cp)

                # Check current result
                a_result = (satisfied_trials / num_trials) > prob_threshold
                lean_list.append(a_result)

            # If the DataGenerator(s) run out of data, return an inconclusive result
            except DataGeneratorException:
                if conf_cp < desired_conf:
                    a_result = None
                else:
                    a_result = (satisfied_trials / num_trials) > prob_threshold
                # print(f'Inconclusive result: {(satisfied_trials / num_trials) > prob_threshold} (confidence: {conf_cp})')
                return a_result, conf_cp, num_trials, satisfied_trials, conf_cp_list, lean_list

        print(f'Conclusive result: {(satisfied_trials / num_trials) > prob_threshold} (confidence: {conf_cp})')
        return a_result, conf_cp, num_trials, satisfied_trials, conf_cp_list, lean_list

    @staticmethod
    def min_num_samples(proportion: float, confidence: float):
        """Find the minimum number of samples to reach a conclusion given the proportion and confidence of the SMC run.
        Based on the number for minimum number of false results to reach a conclusion, and the same for true results.
        Means that for some arbitrarily small/large threshold value, will always reach a conclusion with this number of
        samples.
        """
        n = symbols('n')
        expr_false = - confidence + 1 - (1 - proportion) ** n
        expr_true = - confidence + 1 - proportion ** n

        sol_false = solve(expr_false)
        num_false = ceil(sol_false[0])

        sol_true = solve(expr_true)
        num_true = ceil(sol_true[0])

        return max(num_false, num_true)