#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Mar 20 01:30:55 2018

@author: sina
"""
import subprocess
import os
import sys
import pandas as pd


import shutil as SH
import signal
import time
import argparse as ap




make_process = subprocess.Popen("make clean; make", shell=True, stdout=subprocess.PIPE, stderr=sys.stdout.fileno())
while True:
    line = make_process.stdout.readline()
    if not line:break
    print (line) #output to console in time
    sys.stdout.flush()
    
print('Your code has been compiled')

make_process = subprocess.Popen("./p1_exec 5 6",shell=True, stdout=subprocess.PIPE, stderr=sys.stdout.fileno())
while True:
    line = make_process.stdout.readline()
    if not line:break
    print (line) #output to console in time
    sys.stdout.flush()    


inputPath='input/'
path1='correct_output/'
path2='output/'

inputFiles = [f for f in os.listdir(inputPath) if os.path.isfile(os.path.join(inputPath, f))]

for f in inputFiles:
    f=f.split('.')[0]
    correct_outputs_stats= pd.read_csv(path1+str(f)+'_stats.csv')
    outputs_stats= pd.read_csv(path2+str(f)+'_stats.csv')
    
    print('Is stats file genrated correctly for '+ f +' file? ' + str( correct_outputs_stats.equals(outputs_stats)))
    
    correct_outputs_sorted= pd.read_csv(path1+str(f)+'_sorted.csv')
    outputs_sorted= pd.read_csv(path2+str(f)+'_sorted.csv')
    
    print('Is sorted file genrated correctly for '+ f +' file? ' +str(correct_outputs_sorted.equals(outputs_sorted)))
