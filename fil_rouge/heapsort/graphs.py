import pandas as pd
import matplotlib.pyplot as plt
plt.style.use('seaborn')

merge = pd.read_csv('mergesort.csv')
quick = pd.read_csv('quicksort.csv')
heap = pd.read_csv('heapsort.csv')

merge_deriv = merge['noper'].values[1:]/merge['noper'].values[:-1]
quick_deriv = quick['noper'].values[1:]/quick['noper'].values[:-1]
heap_deriv = heap['noper'].values[1:]/heap['noper'].values[:-1]

plt.subplot(3,2,1)
plt.title('Number of operations')
plt.plot(heap['n'],heap['noper'],color='tab:green',label='Heap sort')
plt.legend(loc='best')

plt.subplot(3,2,2)
plt.title('x[i+1]/x[i]')
plt.plot(heap['n'][1:],heap_deriv,color='tab:green')

plt.subplot(3,2,3)
plt.title('Number of operations')
plt.plot(quick['n'],quick['noper'],color='tab:blue',label='Quick sort')
plt.legend(loc='best')

plt.subplot(3,2,4)
plt.title('x[i+1]/x[i]')
plt.plot(quick['n'][1:],quick_deriv,color='tab:blue')

plt.subplot(3,2,5)
plt.title('Number of operations')
plt.plot(merge['n'],merge['noper'],color='tab:orange',label='Merge sort')
plt.legend(loc='best')

plt.subplot(3,2,6)
plt.title('x[i+1]/x[i]')
plt.plot(merge['n'][1:],merge_deriv,color='tab:orange')

plt.tight_layout()
plt.show()