from sklearn.datasets import load_digits
from sklearn.metrics import accuracy_score
from sklearn.metrics import confusion_matrix
from sklearn.naive_bayes import GaussianNB
from sklearn.model_selection import train_test_split
from sklearn import metrics


def run(d_train, d_test, l_train, l_test):
    classification = GaussianNB()
    classification.fit(d_train, l_train)
    predicted = classification.predict(d_test)
    expected = l_test
    classification_report = metrics.classification_report(expected, predicted)
    accuracy = accuracy_score(expected,predicted)
    confusion = confusion_matrix(expected, predicted)
    return (classification_report,accuracy,confusion,classification)


def validate(classifier,val_data,val_label):
    predicted = classifier.predict(val_data)
    classification_report = metrics.classification_report(val_label, predicted)
    accuracy = accuracy_score(val_label,predicted)
    confusion = confusion_matrix(val_label, predicted)
    return (classification_report,accuracy,confusion)

