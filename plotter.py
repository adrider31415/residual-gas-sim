import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import math
import scipy.stats
from mpl_toolkits.mplot3d import Axes3D
from multiprocessing import Pool
import random
import glob
import os

#change to my path
cpath = "/afs/.ir.stanford.edu/users/c/l/clu2/Documents/gasSimData"


def build_arr(fs):
    arr = np.array([])
    for f in fs:
        arr = np.append(arr, np.loadtxt(f))
    return arr
        

def get_data(path):
    xfs = glob.glob(os.path.join(path, "*x.txt"))
    yfs = glob.glob(os.path.join(path, "*y.txt"))
    zfs = glob.glob(os.path.join(path, "*z.txt"))
    return build_arr(xfs),  build_arr(yfs),  build_arr(zfs)


class Fstats:
    def __init__(self, xa, ya, za, n):
        self.fs = np.array([xa, ya, za])
        self.n = n
        self.nsim = len(xa)

def gauss(x, *p):
    #a gaussian function for fitting to distributuions
    A, mu, sigma = p
    return A*np.exp(-(x-mu)**2/(2.*sigma**2))

def fit_fdist(fsobj, axis = 0, npb = 10., p0 = [100.,0., 0.00002]):
    #plots histogram of average force during simulation.
    nbins = int(len(fsobj.fs[axis, :])/npb)
    h, be = np.histogram(fsobj.fs[axis, :], nbins)
    bc = (be[1:] + be[:-1])/2.
    popt, pcov = curve_fit(gauss, bc, h, p0 = p0)
    mustr = '{:.2e}'.format(popt[1])
    sigstr = '{:.2e}'.format(np.sqrt(pcov[1, 1]))
    pltx = np.linspace(np.min(bc), np.max(bc), 100)
    plt.plot(pltx, gauss(pltx, *popt), label = \
             'mean ' + mustr+" $\pm$ " +sigstr, linewidth = 2.)
    plt.hist(fsobj.fs[axis, :], nbins)
    plt.xlabel('Force after %i collisions'%fsobj.nsim)
    plt.ylabel('Frequency in %i simulations'%fsobj.n)
    plt.legend()
    plt.show()
    return pcov

def plter(xarr, yarr, zarr):
    #plots the trajectories
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.plot(xarr, yarr, zarr, '.-')
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')
    #ax.set_xlim([-1, 1])
    #ax.set_ylim([-1, 1])
    #ax.set_zlim([-1, 1])
    plt.show()

xarr, yarr, zarr = get_data(cpath) 
fsobj = Fstats(xarr, yarr, zarr, 10000000)
fit_fdist(fsobj, axis = 1)

#plter(xarr, yarr, zarr)
