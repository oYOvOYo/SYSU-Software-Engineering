import helper
import submission

training_data = helper.read_data('./asset/training_data.txt')
classifier_path = './asset/classifier.dat'
submission.train(training_data, classifier_path)

test_data = helper.read_data('./asset/tiny_test.txt')
prediction = submission.test(test_data, classifier_path)
print(prediction) 