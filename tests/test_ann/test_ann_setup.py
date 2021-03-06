#*********************************************************************************
#* Copyright (C) 2015-2016 Alexey V. Akimov
#*
#* This file is distributed under the terms of the GNU General Public License
#* as published by the Free Software Foundation, either version 2 of
#* the License, or (at your option) any later version.
#* See the file LICENSE in the root directory of this distribution
#* or <http://www.gnu.org/licenses/>.
#*
#*********************************************************************************/

import os
import sys
import math

# Fisrt, we add the location of the library to test to the PYTHON path
if sys.platform=="cygwin":
    from cyglibra_core import *
elif sys.platform=="linux" or sys.platform=="linux2":
    from liblibra_core import *
from libra_py import *



print "\nTest 2: Default constructor"
print "ANN = NeuralNetwork()"
ANN = NeuralNetwork()


print "\nTest 2a: ShowANN"
print "ANN.ShowANN()"
ANN.ShowANN()


print "\nTest 3: Setting up the ANN architecture and initializing weights"
ANN.CreateANN([2,5,1])

print "\nTest 3a: ShowANN"
print "ANN.ShowANN()"
ANN.ShowANN()


print "\nTest4: Export ANN"
print "ANN.ExportANN(\"initial.ann\")"
ANN.ExportANN("initial.ann")


                                                                 
print "\nTest 5: Setting up data: \"set_training_data\" function"
print "Warning!!!: It doesn't work without Derivs... so you have to supply them even if you don't actually use them - (may be just set to zeros)"
print "The data consists of a collection of what is called patterns. Each pattern is a pair of n-vector containing input, and m-vector containing output"
print "Binary logic: AND pattern"

print "p1 = tmp()"
print "p1.Input = [0,0]"
print "p1.Output = [0]"
print "p2 = tmp()"
print "p2.Input = [1,0]"
print "p2.Output = [0]"
print "p3 = tmp()"
print "p3.Input = [0,1]"
print "p3.Output = [0]"
print "p4 = tmp()"
print "p4.Input = [0,0]"
print "p4.Output = [1]"

print "training_set = [p1,p2,p3,p4]"
print "ANN.SetTrainingData(training_set,0)"


class patt():
    pass
p1 = patt()
p1.Input = [0.0, 0.0]
p1.Output = [0.0]
p1.Derivs = [ 0.0,0.0 ]
print p1

p2 = patt()
p2.Input = [1,0]
p2.Output = [0]
p2.Derivs = [ 0.0,0.0 ]
print p2

p3 = patt()
p3.Input = [0,1]
p3.Output = [0]
p3.Derivs = [ 0.0,0.0 ]
print p3

p4 = patt()
p4.Input = [1,1]
p4.Output = [1]
p4.Derivs = [ 0.0,0.0 ]
print p4

training_set = [ p1,p2,p3,p4]
ANN.SetTrainingData(training_set,1)


print "\nTest5a: Export ANN"
print "ANN.ExportANN(\"initial_withdata.ann\")"
ANN.ExportANN("initial_withdata.ann")


print "\nTest6: Import ANN"
print "ANN1 = NeuralNetwork()"
print "ANN1.ImportANN(\"initial_withdata.ann\")"
ANN1 = NeuralNetwork()
ANN1.ImportANN("initial_withdata.ann")


print "\nTest7: ScaleTrainingData"
print "Use ANN1.ScaleTrainingData(1,0) to scale input to [-0.95,0.95] range\n"
print "Use ANN1.ScaleTrainingData(0,1) to scale output to [-0.95,0.95] range\n"
print "Use ANN1.ScaleTrainingData(1,1) to scale both input and output to [-0.95,0.95] range\n"
print "--------------------------------------"
print "ANN1.ImportANN(\"initial_withdata.ann\")"
ANN1.ImportANN("initial_withdata.ann")

print "ANN1.SetTrainingData(training_set,1)"
ANN1.SetTrainingData(training_set,1)

print "ANN1.ScaleTrainingData(1,1)"
ANN1.ScaleTrainingData(1,1)

print "ANN1.ExportANN(\"initial_withdata_scaled_1_1.ann\")"
ANN1.ExportANN("initial_withdata_scaled_1_1.ann")

print "Check the data in \"initial_withdata_scaled_1_1.ann\" file"



print "\nTest8: ANN Training"
print "Here we will try to train our ANN, but it will fail - bacause we also need to configure how the training is done"
print "See this in the next test: test_training.py"
print "For now we do just..."
print "ANN1.ANNTrain()"
ANN1.ANNTrain()


