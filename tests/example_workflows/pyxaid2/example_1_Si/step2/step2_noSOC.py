#***********************************************************
# * Copyright (C) 2017-2018 Brendan A. Smith and Alexey V. Akimov
# * This file is distributed under the terms of the
# * GNU General Public License as published by the
# * Free Software Foundation; either version 3 of the
# * License, or (at your option) any later version.
# * http://www.gnu.org/copyleft/gpl.txt
#***********************************************************/
import os
import sys
import time
import math

# Fisrt, we add the location of the library to test to the PYTHON path
if sys.platform=="cygwin":
    from cyglibra_core import *
elif sys.platform=="linux" or sys.platform=="linux2":
    from liblibra_core import *

from libra_py import *


nsteps_per_job = 25
tot_nsteps = 25

os.system("mkdir res")
QE_methods.out2inp("x0.md.out","x0.scf.in","wd","x0.scf",0,tot_nsteps,1)

os.system("cp submit_templ.slm wd"); os.system("cp x0.exp.in wd"); os.chdir("wd")
hpc_utils.distribute(0,tot_nsteps,nsteps_per_job,"submit_templ.slm",["x0.exp.in"],["x0.scf"],2)

