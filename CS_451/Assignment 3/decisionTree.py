from sklearn.datasets import load_digits
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix
from sklearn.tree import DecisionTreeClassifier
from sklearn import metrics
from sklearn.metrics import accuracy_score

def run(criterion:str, splitter:str, d_train, d_test, l_train, l_test):
    classification = DecisionTreeClassifier(criterion=criterion,splitter=splitter)
    classification.fit(d_train,l_train)
    predicted = classification.predict(d_test)
    classification_report = metrics.classification_report(l_test, predicted)
    confusion = confusion_matrix(l_test, predicted)
    accuracy = accuracy_score(l_test,predicted)
    return (classification_report,accuracy,confusion,classification)


def validate(classifier,val_data,val_label):
    predicted = classifier.predict(val_data)
    classification_report = metrics.classification_report(val_label, predicted)
    accuracy = accuracy_score(val_label,predicted)
    confusion = confusion_matrix(val_label, predicted)
    return (classification_report,accuracy,confusion)