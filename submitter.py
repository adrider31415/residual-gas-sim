import os
import subprocess
import time

#need to change to your working directory.
outpath = "/afs/.ir.stanford.edu/users/c/l/clu2/Documents/gasSimData"
if not os.path.exists(outpath):
    os.makedirs(outpath)
#check path exists, if not creates
    print outpath


exe = './simfuncl.o'
numinq = 480

def count_q():
    #counts my jobs
    output = subprocess.check_output(['qstat'])
    tempn = output.count("\n")
    if tempn> 0:
        return tempn - 2
    else:
        return 0

def top_off_que(n, find_start):
    #adds jobs to the que to keep n in the que. returns the next file index.
    nq = count_q()
    for j in range(n - nq):
        fstr = os.path.join(outpath, str(j + find_start))
        print fstr
        output = subprocess.check_output(['qsub', '-V', '-cwd', '-b y',
                                          exe, fstr])
        print output
    return n-nq + find_start

find_start = 480*os.getpid()#start at 480*pid so consecutive pids dont lead to overlapping filenames.
while True:
    find_start = top_off_que(numinq, find_start)
    time.sleep(60)
   
