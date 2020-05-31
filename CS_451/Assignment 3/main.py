from sklearn.decomposition import PCA
import decisionTree
import naiveBayes
import kNearest
from sklearn.model_selection import train_test_split
from sklearn import datasets
from sklearn.datasets import load_digits
import numpy as np
import time

mnist = datasets.fetch_openml('mnist_784') #MNIST
d_train, d_test, l_train, l_test = train_test_split(np.array(mnist.data), mnist.target,test_size=0.20, random_state=50) #Training and testing
d_train, val_data, l_train, validation_label = train_test_split(d_train, l_train,test_size=0.1, random_state=100) #Validating
#d data -- l label
pca_data = PCA(.95) #PCA
pca_data.fit(d_train)
val_data = pca_data.transform(val_data)
d_train = pca_data.transform(d_train)
d_test = pca_data.transform(d_test)

print("---- Labels ----")
print('Size: '+ str(len(l_test)))
print("----------------")


print('--- Decision Tree ---\n')
splitter  = ['best','random']
criterion = ['entropy','gini']
for criteration_test in criterion:
    for splitter_test in splitter:
        print("Criterion = " + criteration_test +  " and Splitter = " + splitter_test + "\n" )
        start = time.time()
        res = decisionTree.run(criteration_test, splitter_test,d_train, d_test, l_train, l_test)
        classifier = res[3]
        print("Class Report\n"+ str(res[0])+ " Accuracy: " + str(res[1]) + "\nConfusion Matrix:\n" + str(res[2]) + "\n")
        print('t: '+ str(time.time()-start))
        print("Validate \n")
        validate = decisionTree.validate(classifier,val_data,validation_label)
        print("Class Report\n" + str(validate[0]) + " Accuracy: "+ str(validate[1]) + "\nConfusion Matrix:\n"+ str(validate[2]) + "\n")


print('--- K Nearest Neighbors ---\n')
n_count_test = [2,4,6,8,10]
for n_count in n_count_test:  
    print("KNearest with n_count=" + str(n_count) + "\n")
    start = time.time()
    res = kNearest.run(d_train, d_test, l_train, l_test,n_count)
    classifier = res[3]
    print("Class Report\n"+str(res[0]) + " Accuracy: " +str(res[1])+ "\nConfusion Matrix:\n" +str(res[2])+ "\n")
    print('t:'+ str(time.time()-start))
    print("Validate \n")
    validate = kNearest.validate(classifier,val_data,validation_label)
    print("Class Report\n" + str(validate[0]) + " Accuracy: " + str(validate[1]) + "\nConfusion Matrix:\n " + str(validate[2])+ "\n")

print('--- Naive Bayes ---\n')
start = time.time()
res = naiveBayes.run(d_train, d_test, l_train, l_test)
classifier = res[3]
print("Class Report\n"  + str(res[0]) + " Accuracy:" + str(res[1]) + "\nConfusion Matrix:\n" + str(res[2]) + "\n")
print('t: '+ str(time.time()-start))
print("Validate \n")
validate = naiveBayes.validate(classifier,val_data,validation_label)
print("Class Report\n" + str(validate[0]) + " Accuracy:" + str(validate[1])+ "\nConfusion Matrix:\n" + str(validate[2]) + "\n")

print("\n--- THE END ---\n")
        
        
