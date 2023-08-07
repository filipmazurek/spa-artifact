from scipy import stats
from statistics import mean, variance


def separation_test(data1, data2):
    """Perform a two-sample t-test on the given data.
    Return the t-statistic"""
    assert(len(data1) == len(data2))
    # Perform the two-sample t-test.
    t = (mean(data1) - mean(data2)) / (((variance(data1) + variance(data2)) / len(data1)) ** 0.5)
    # Return t value for certainty in separation
    # print(f't: {t}')
    return t

def significance_from_separation_test(data1, data2, significance=0.05):
    """Returns the t-value from the separation test, as well as the T value to compare to.
    The T value returned is based on the alternate hypothesis that the runtimes of data1 are slower than data2. 
    Meaning that if T > t, then the null hypothesis (means are equal) is rejected, and the alternate (d1 is slower than d2) is accepted
    """
    assert(len(data1) == len(data2))
    T = separation_test(data1, data2)
    # If equal variances are assumed, then can use df = 2*num_samples - 2
    # deg_freedom = 2*len(data1) - 2
    # Otherwise use a different formula
    var_1 = variance(data1)
    var_2 = variance(data2)
    n_s = len(data1)

    # Degrees of freedom: if not assuming equal variances
    # deg_freedom = pow((var_1 + var_2)/n_s, 2) / ((pow(var_1/n_s, 2) + pow(var_2/n_s, 2))/n_s-1)
    # If do assume equal variance, then the formula is much simpler
    deg_freedom = 2 * n_s - 2

    # Calculate the corresponding t-value
    # One-ended test, where the alternative is mean_1 < mean_2 (instead of inequality)
    # https://www.itl.nist.gov/div898/handbook/eda/section3/eda353.htm
    t = stats.t.ppf(q=1-significance,df=deg_freedom)

    # Calculate significance
    # The significance level was already set to be 95%. That's an input to the function. As a result, the below should always return that value
    # if testing with the "t" value
    sig = 1 - stats.t.cdf(T, deg_freedom)
    # print(sig)

    return T, t


def modified_proportion_two_sample_t_test(data1, data2, proportion, significance):
    """
    T-test modified to more directly compare the SMC technique using HPSTL. Takes in a proportion, which is 
    the factor of by how much one distribution has to be "shifted" by the other one.
    Note that significance is 1-conf, meaning 0.05 for a 0.95 confidence level
    """
    assert(len(data1) == len(data2))

    var_1 = variance(data1)
    var_2 = variance(data2)
    n_s = len(data1)

    deg_freedom = 2 * n_s - 2

    # The original two-sample t-test
    T = (mean(data1) - mean(data2)) / (((var_1 + var_2) / len(data1)) ** 0.5)

    # PPF: to find the ciritical t-value at this proportion
    # Get the Gaussian distribution ppf at the desired proportion
    gaussian_proportion_cdf = stats.norm.ppf(proportion)

    # The comparative value for the resulting t-distribution compared to the gaussian assumed distribution
    proportion_comparison_result = T - gaussian_proportion_cdf

    # The value to compare against to see if it matches the desired significance

    t = stats.t.ppf(q=1-significance,df=deg_freedom)

    # Result if the t-test alternate hypothesis is accepted or rejected
    result_for_confidence = proportion_comparison_result > t

    # The final confidence is the cdf of the particular t-distribution
    confidence = stats.t.cdf(proportion_comparison_result, deg_freedom)


    return T, t, proportion_comparison_result, result_for_confidence, confidence


def modified_threshold_two_sample_t_test(data1, threshold, proportion, significance):
    """
    A modified t-test that takes in a threshold, and compares the mean of the first distribution to the threshold.
    """
    var_1 = variance(data1)
    var_2 = 0
    n_s = len(data1)

    deg_freedom = 2 * n_s - 2

    # The original two-sample t-test
    T = (mean(data1) - threshold) / (((var_1 + var_2) / len(data1)) ** 0.5)

    # PPF: to find the ciritical t-value at this proportion
    # Get the Gaussian distribution ppf at the desired proportion
    gaussian_proportion_cdf = stats.norm.ppf(proportion)

    # The comparative value for the resulting t-distribution compared to the gaussian assumed distribution
    proportion_comparison_result = T - gaussian_proportion_cdf

    # The value to compare against to see if it matches the desired significance

    t = stats.t.ppf(q=1-significance,df=deg_freedom)

    # Result if the t-test alternate hypothesis is accepted or rejected
    result_for_confidence = proportion_comparison_result > t

    # The final confidence is the cdf of the particular t-distribution
    confidence = stats.t.cdf(proportion_comparison_result, deg_freedom)


    return T, t, proportion_comparison_result, result_for_confidence, confidence