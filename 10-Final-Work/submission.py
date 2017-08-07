import pandas as pd
import numpy as np
import pickle
from sklearn.naive_bayes import MultinomialNB
from sklearn.preprocessing import LabelEncoder
from sklearn.feature_extraction import DictVectorizer
from sklearn.externals import joblib


def get_world(line):
    return line.split(":")[0]

def get_phonemes(line):
    return line.split(":")[1]

def has_number(string):
    return any(char.isdigit() for char in string)

def get_stress_index(vowels_list):
    return [i + 1 for i, x in enumerate(vowels_list) if "1" in x][0]

def get_data_1(line):
    line = get_phonemes(line)
    phonemes_list = line.split(" ")
    vowels_list = list(filter(lambda phoneme: has_number(phoneme), phonemes_list))
    # return [get_stress_index(vowels_list), line.replace("0", "").replace("1", "").replace("2", "")]
    for i in range(len(phonemes_list)):
        phonemes_list[i] = str(i) + phonemes_list[i]
    return [get_stress_index(vowels_list), " ".join(phonemes_list)]

def get_data_2(line):
    line = get_phonemes(line)
    phonemes_list = line.split(" ")
    vowels_list = list(filter(lambda phoneme: has_number(phoneme), phonemes_list))
    # return [get_stress_index(vowels_list), line.replace("0", "").replace("1", "").replace("2", "")]
    for i in range(len(phonemes_list)):
        phonemes_list[i] = str(i) + phonemes_list[i]
    return [0, " ".join(phonemes_list)]

def get_freq_of_tokens(sms):
    tokens = {}
    for token in sms.split(' '):
        if token not in tokens:
            tokens[token] = 1
        else:
            tokens[token] += 1
    return tokens

################# training #################

def train(data, classifier_file):# do not change the heading of the function
    train_data = data
    train = pd.DataFrame([get_data_1(line) for line in train_data], 
                  index=[get_world(line) for line in train_data],
                  columns=["type", "text"])
    x_train = [ get_freq_of_tokens(text) for text in  train.text ]
    y_train = train.type

    encoder = LabelEncoder()
    vectorizer = DictVectorizer(dtype=float, sparse=True)
    nb = MultinomialNB(alpha=1)

    x = vectorizer.fit_transform(x_train)
    # y = encoder.fit_transform(y_train)
    y = y_train    
    nb.fit(x, y)
    joblib.dump([nb, encoder, vectorizer], classifier_file) 

################# testing #################

def test(data, classifier_file):# do not change the heading of the function
    nb, encoder, vectorizer = joblib.load(classifier_file)
    
    train_data = data
    train = pd.DataFrame([get_data_2(line) for line in train_data], 
                  index=[get_world(line) for line in train_data],
                  columns=["type", "text"])
    x_train = [ get_freq_of_tokens(text) for text in  train.text ]
    x = vectorizer.transform(x_train)

    return list(nb.predict(x))
