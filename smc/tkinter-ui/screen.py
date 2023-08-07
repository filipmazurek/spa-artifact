from tkinter import *
import os
#from smc.smc_engine.property_specification import 
from tkinter import filedialog as fd
from smc.spa_frontend.support_maps import DATA_SOURCE_DESCRIPTIONS, PROPERTIES_DESCRIPTIONS, PROPERTIES_MAP
from smc.spa_frontend.spa import run_frontend
from datetime import datetime
import re


def raise_frame(frame):
    frame.tkraise()

root = Tk()
root.geometry('500x500')
root.title("SMC for Processor Analysis")

smc_spa_frame = Frame(root)
smc_spa_frame.grid(row=0, column=0, sticky='news')

method = 'SMC'
var_method = StringVar()
var_method.set('SMC')

def print_selection():
    global method
    method = var_method.get()
    if method == 'SMC':
        backButton2.pack_forget()
        nextButton2.pack_forget()
        thresholdLabel.pack()
        thresholdInput.pack()
        backButton2.pack()
        nextButton2.pack()
    else:
        thresholdLabel.pack_forget()
        thresholdInput.pack_forget()


Label(smc_spa_frame, text="Select evaluation method").pack()
r1 = Radiobutton(smc_spa_frame, text='SMC', val='SMC', variable=var_method, command=print_selection)
r1.pack()
r2 = Radiobutton(smc_spa_frame, text='SPA', val='SPA', variable=var_method, command=print_selection)
r2.pack()
nextButton2 = Button(smc_spa_frame, text='Next', command=lambda:raise_frame(specs_frame))
nextButton2.pack(side='left')

# page 1
specs_frame = Frame(root)
specs_frame.grid(row=0, column=0, sticky='news')

confidence = 0
proportion = 0
SMCthreshold = 0
def confidenceEdited(e):
    global confidence
    confidence = confidenceInput.get(1.0, "end-1c")

def proportionEdited(e):
    global proportion
    proportion = proportionInput.get(1.0, "end-1c")

def thresholdEdited(e):
    global SMCthreshold
    SMCthreshold = thresholdInput.get(1.0, "end-1c")

Label(specs_frame, text='Input Confidence').pack()
confidenceInput = Text(specs_frame, height = 2, width = 20)
confidenceInput.pack()
confidenceInput.bind('<KeyRelease>',confidenceEdited)
Label(specs_frame, text='Input Proportion').pack()
proportionInput = Text(specs_frame, height = 2, width = 20)
proportionInput.pack()
proportionInput.bind('<KeyRelease>',proportionEdited)
Label(specs_frame, text="Select Property (from runtime.py file)").pack()

smcProperty = 0
numberOfInputs = IntVar()
properties = PROPERTIES_MAP
keySet = list(properties.keys())
def propertyButton():
    global smcProperty
    global prop
    global numberOfInputs
    smcProperty = properties[propertyClicked.get()]['class']
    print("smc.smc_engine.property_specification."+smcProperty)
    import smc.smc_engine.property_specification
    prop = getattr(smc.smc_engine.property_specification, smcProperty)
    numberOfInputs.set(prop.NUM_SOURCES)
    print(smcProperty, prop, numberOfInputs.get())

    if numberOfInputs.get() == 1:
        for component in second_components:
            component.pack_forget()
    elif numberOfInputs.get() == 2:
        nextButton3.pack_forget()
        backButton3.pack_forget()
        for component in second_components:
            component.pack()
        nextButton3.pack()
        backButton3.pack()
    root.update()
    
propertyClicked = StringVar()
propertyClicked.set(1)

for x in range(0, len(properties)):
    keySet = list(properties.keys())
    r1 = Radiobutton(specs_frame, text=keySet[x], val=keySet[x], variable=propertyClicked, command=propertyButton)
    r1.pack()

thresholdLabel = Label(specs_frame, text='Input SMC Threshold Assertion')
thresholdInput = Text(specs_frame, height = 2, width = 20)
thresholdLabel.pack()
thresholdInput.pack()
thresholdInput.bind('<KeyRelease>',thresholdEdited)

backButton2 = Button(specs_frame, text='Back', command=lambda:raise_frame(smc_spa_frame))
backButton2.pack(side='left')

data_input_frame = Frame(root)
data_input_frame.grid(row=0, column=0, sticky='news')

nextButton2 = Button(specs_frame, text='Next', command=lambda:raise_frame(data_input_frame))
nextButton2.pack(side='left')

# page 2
Label(data_input_frame, text="Select Data Source Type").pack()
sourceType1 = 0
csvInput1 = 0
csvInput2 = 0
def gem5Source1():
    global csvInput1
    filename = "stats.txt"
    key = 'system.ruby.l2_cntrl0.L2cache.m_demand_misses'

    regex = f'(?<={key})\s+(\d+(?:\.\d+)?)'
    results = []
    result_vals =[]
    baseline_vals = []

    csvtitle = 'gem5source1-' + str(datetime.now().strftime('%Y%m-%d%H-%M%S')) + '.csv'
    

    from tkinter import filedialog
    path = filedialog.askdirectory()
    file_list = []
    for root, dirs, files in os.walk(path):
        for file in files:
            print(root + "/" +file)
            file_list.append(root + "/" +file)
    file_list.sort(key=lambda x: os.path.getmtime(x))

    for path in file_list:
        if path.split("/")[-1] == filename:
            with open(path, 'r') as f:
                try:
                    value = re.search(regex, f.read())
                    value = int(value.group(0)) 
                except AttributeError:
                    continue

                results.append({'value': value, 'path': path})
                result_vals.append(value)
                    
    
    print(f'{len(result_vals)} values found!')

    print('writing to CSV File')
    import csv
    with open(csvtitle, 'w') as file:
        writer = csv.writer(file, dialect='excel')
        writer.writerow(result_vals)
        print('finished writing')

    csvInput1 = csvtitle
    print(csvInput1)
    input_label.configure(text=csvInput1.split('/')[-1])
    root.update()

def gem5Source2():
    global csvInput2
    filename = "stats.txt"
    key = 'system.ruby.l2_cntrl0.L2cache.m_demand_misses'

    regex = f'(?<={key})\s+(\d+(?:\.\d+)?)'
    results = []
    result_vals =[]
    baseline_vals = []

    csvtitle = 'gem5source1-' + str(datetime.now().strftime('%Y%m-%d%H-%M%S')) + '.csv'
    

    from tkinter import filedialog
    path = filedialog.askdirectory()
    file_list = []
    for root, dirs, files in os.walk(path):
        for file in files:
            print(root + "/" +file)
            file_list.append(root + "/" +file)
    file_list.sort(key=lambda x: os.path.getmtime(x))

    for path in file_list:
        if path.split("/")[-1] == filename:
            with open(path, 'r') as f:
                try:
                    value = re.search(regex, f.read())
                    value = int(value.group(0)) 
                except AttributeError:
                    continue

                results.append({'value': value, 'path': path})
                result_vals.append(value)
                    
    
    print(f'{len(result_vals)} values found!')

    print('writing to CSV File')
    import csv
    with open(csvtitle, 'w') as file:
        writer = csv.writer(file, dialect='excel')
        writer.writerow(result_vals)
        print('finished writing')

    csvInput2 = csvtitle
    print(csvInput2)
    input_label2.configure(text=csvInput2.split('/')[-1])
    root.update()
    

def csvSource1():
    global csvInput1
    csvInput1 = fd.askopenfilename()
    print(csvInput1)
    input_label.configure(text=csvInput1.split('/')[-1])
    root.update()

def csvSource2():
    global csvInput2
    csvInput2 = fd.askopenfilename()
    print(csvInput2)
    input_label2.configure(text=csvInput2.split('/')[-1])
    root.update()
  
sourceClicked1 = StringVar()
sourceClicked1.set( "Statistic" )
second_components = []

# data source 1
x = 1
# radio_label = Label(data_input_frame, text="Select Data Source Type for Input " + str(x))
# radio_label.pack()
# r1 = Radiobutton(data_input_frame, text='Statistic', val='Statistic', variable=sourceClicked1, command=sourceTypeButton1)
# r2 = Radiobutton(data_input_frame, text='Event Log', val='Event Log', variable=sourceClicked1, command=sourceTypeButton1)
# r1.pack()
# r2.pack()
button_label = Label(data_input_frame, text="Select File Format for Input 1")
button_label.pack()
b1 = Button(data_input_frame, text='Raw gem5 output', command=gem5Source1)
b2 = Button(data_input_frame, text='CSV file', command=csvSource1, bg="blue")
b1.pack()
b2.pack()
input_label = Label(data_input_frame, text="No input file selected")
input_label.pack()
#input_components.append([radio_label, r1, r2, button_label, b1, b2])

# data source 2
x = 2
#radio_label = Label(data_input_frame, text="Select Data Source Type for Input " + str(x))
#radio_label.pack()
#r1 = Radiobutton(data_input_frame, text='Statistic', val='Statistic', variable=sourceClicked, command=sourceTypeButton)
#r2 = Radiobutton(data_input_frame, text='Event Log', val='Event Log', variable=sourceClicked, command=sourceTypeButton)
#r1.pack()
#r2.pack()
button_label2 = Label(data_input_frame, text="Select File Format for Input 2")
#button_label2.pack()
b1_2 = Button(data_input_frame, text='Raw gem5 output', command=gem5Source2)
b2_2 = Button(data_input_frame, text='CSV file', command=csvSource2)
input_label2 = Label(data_input_frame, text="No input file selected")
#input_label.pack()
#b1.pack()
#b2.pack()
second_components.append(button_label2)
second_components.append(b1_2)
second_components.append(b2_2)
second_components.append(input_label2)

backButton3 = Button(data_input_frame, text='Back', command=lambda:raise_frame(specs_frame))
backButton3.pack()

run_smc_frame = Frame(root)
run_smc_frame.grid(row=0, column=0, sticky='news')

nextButton3 = Button(data_input_frame, text='Next', command=lambda:raise_frame(run_smc_frame))
nextButton3.pack(side='left')


#runSMC frame
results = ""
def runSMC():
    global results

    import argparse
    args = argparse.Namespace
    args.property = [smcProperty]
    args.data_source = [csvInput1]
    if numberOfInputs.get() == 2:
        args.data_source_2 = [csvInput2]
    else:
        args.data_source_2 = None
    if method == "SPA":
        args.smc_only = False
    else:
        args.smc_only = True
    args.threshold = [float(SMCthreshold)]
    args.granularity = None
    args.proportion = float(proportion)
    args.confidence = float(confidence)
    args.search_start_point = None
    args.iteration_limit = 10000

    results = run_frontend(args)
    viewText = ""
    if method == 'SMC':
        output_location = writeFileSMC()
        viewText = "SMC Results\n"
        viewText+="Assertion = " + str(results[3])
        viewText+="\nFull output saved to " + output_location
    else:
        output_location = writeFileSPA()
        viewText = "SPA Results\n"
        viewText+="Assertion Range between " + str(results[3]) + " and " + str(results[4])
        viewText+="\nFull output saved to " + output_location

    run_result_label.configure(text=viewText)
    root.update()

run_btn_label = Label(run_smc_frame, text="Run SMC/SPA on Inputted Data")
run_btn_label.pack()

runBtn = Button(run_smc_frame, text='RUN', command=runSMC)
runBtn.pack()


run_result_label = Label(run_smc_frame, text="Click run to view resutls")
run_result_label.pack()

def writeFileSPA():
    output_location = 'SPA-' + str(datetime.now().strftime('%Y%m-%d%H-%M%S')) + '.txt'
    file = open(output_location,'a+')
    file.write('Time of execution = ' + str(datetime.now().strftime("%m/%d/%Y, %H:%M:%S")))
    file.write('\nType of execution = SPA ' + smcProperty)
    file.write('\nInput source 1 = ' + csvInput1)
    if numberOfInputs.get() == 2:
        file.write('\nInput source 2 = ' + csvInput2)
    file.write('\nConfidence = ' + confidence)
    file.write('\nProportion = ' + proportion)
    file.write('\nOutput Lower Bound = ' + str(results[3]))
    file.write('\nOutput Upper Bound = ' + str(results[4]))
    file.close()
    return output_location

def writeFileSMC():
    output_location = 'SMC-' + str(datetime.now().strftime('%Y%m-%d%H-%M%S')) + '.txt'
    file = open(output_location,'a+')
    file.write('Time of execution = ' + str(datetime.now().strftime("%m/%d/%Y, %H:%M:%S")))
    file.write('\nType of execution = SMC ' + smcProperty)
    file.write('\nInput source 1 = ' + csvInput1)
    if numberOfInputs.get() == 2:
        file.write('\nInput source 2 = ' + csvInput2)
    file.write('\nConfidence = ' + confidence)
    file.write('\nProportion = ' + proportion)
    file.write('\nAssertion Threshold = ' +  str(results[0]))
    file.write('\nOutput Assertion = ' + str(results[3]))
    file.close()
    return output_location

raise_frame(smc_spa_frame)
root.mainloop()
root.update()