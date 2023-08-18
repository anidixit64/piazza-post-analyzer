//
//  main.cpp
//  p5-ml
//
//  Created by Aniket Dixit on 4/2/23.
//  Project UID db1f506d06d84ab787baf250c265e24e

#include <iostream>
#include <map>
#include <string>
#include <set>
#include <cmath>
#include "csvstream.h"

using namespace std;

class MVBNBC {
public:
    MVBNBC(): debug(false), totalCount(0), numUniqWords(0) {};
    
    void setDebug() {
        debug = true;
    }
    
    // EFFECTS: Return a set of unique whitespace delimited words.x
    set<string> unique_words(const string &str) {
      istringstream source(str);
      set<string> words;
      string word;
      while (source >> word) {
        words.insert(word);
      }
      return words;
    }

    // trains on databaseuni
    void training(csvstream &file) {
        
        int count = 0;
        string label = "";
        string content = "";
        
        map<string, string> row;
        
        if (debug) {
            cout << "training data:" << endl;
        }
        
        while (file >> row) {
            count++;
            label = row["tag"];
            content = row["content"];
            
            labels.insert(label);
            set<string> uniqWords = unique_words(content);
            
            labelCounts[label]++;
            
            for (const auto& word: uniqWords){
                pair<string, string> combos;
                combos.first = label;
                combos.second = word;
                wordCounts[word]++;
                condCounts[combos]++;
            }
            
            if (debug) {
                cout << "  label = " << label << ", content = " << content << "\n";
            }
        }
        
        numUniqWords = wordCounts.size();
        totalCount += count;
        
        for (auto l: labels) {
            labelProb[l] = calcLogPrior(l);
        }
        
        cout << "trained on " << count << " examples\n";
        
        if (debug) {
            cout << "vocabulary size = " << numUniqWords << "\n";
        }
        
        cout << "\n";
    }
    
    double calcLogPrior(string labelIn) {
        return log((labelCounts[labelIn])/totalCount);
    }
    
    double calcLogLiklihood(string content, string label) {
        double labellog = labelProb[label];
        set<string> uniqWords = unique_words(content);
        
        for (auto words: uniqWords) {
            if (wordCounts[words] == 0) {
                labellog += log(1.0/totalCount);
            }
            else {
                pair<string, string> labelWord;
                labelWord.first = label;
                labelWord.second = words;
                if (condCounts[labelWord] == 0) {
                    labellog += log((wordCounts[words])/totalCount);
                }
                else {
                    labellog += log((condCounts[labelWord])/(labelCounts[label]));
                }
            }
        }
        
        return labellog;
    }
    
    pair<string, double> predict(string c) {
        vector<pair<string, double>> calculate;
        
        for (auto l: labels) {
            double logCalc = calcLogLiklihood(c, l);
            pair<string, double> add;
            add.first = l;
            add.second = logCalc;
            calculate.push_back(add);
        }
        
        pair<string, double> max = calculate[0];
        for (auto p: calculate) {
            if (p.second > max.second) {
                max = p;
            }
            
            if (p.second == max.second) {
                if (p.first < max.first) {
                    max = p;
                }
            }
        }
        
        return max;
    }
    
    void debugCode() {
        cout << "classes:\n";
        for (auto l: labels) {
            cout << "  " << l << ", " << labelCounts[l];
            cout << " examples, log-prior = " << labelProb[l];
            cout << "\n";
        }
        
        cout << "classifier parameters:\n";
        for (auto part: condCounts) {
            string label = (part.first).first;
            string word = (part.first).second;
            int count = (part.second);
            double logl = log(count/labelCounts[label]);
            
            cout << "  ";
            cout << label << ":" << word << ", count = ";
            cout << count << ", log-likelihood = " << logl;
            cout << "\n";
        }
        
        cout << "\n";
    }
    
    void testing(csvstream &inFile) {
        map<string, string> row;
        string label;
        string content;
        
        int numCorrect = 0;
        int numTotal = 0;
        
        cout << "test data:\n";
        while (inFile >> row) {
            label = row["tag"];
            content = row["content"];
            
            pair<string, double> answer = predict(content);
            
            cout << "  ";
            cout << "correct = " << label << ", predicted = ";
            cout << answer.first << ", log-probability score = " << answer.second;
            cout << "\n  " << "content = " << content << "\n\n";
            
            if (answer.first == label) {
                numCorrect++;
            }
            numTotal++;
        }
        
        cout << "performance: " << numCorrect << " / " << numTotal;
        cout << " posts predicted correctly\n";
    }
    
private:
    bool debug;
    int totalCount;
    int numUniqWords;
    map<string, double> labelCounts;
    map<string, double> wordCounts;
    map<pair<string, string>, int> condCounts;
    map<string, double> labelProb;
    set<string> labels;
    map<string, double> wordsProb;
    
};

int main(int argc, const char * argv[]) {
    cout.precision(3);
    
    if (argc != 3 && argc != 4) {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 2;
    }
    
    if (argc == 4) {
        string d = argv[3];
        if (d != "--debug") {
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
            return 2;
        }
    }
    
    
    string junk = argv[0];
    const string trainingFile = argv[1];
    const string testFile = argv[2];
    
    bool debugSet = false;
    
    
    ifstream fin1(trainingFile);
    if (!fin1.is_open()){
        cout << "Error opening file: " << trainingFile << endl;
        return 2;
    }
    fin1.close();

    ifstream fin2(testFile);
    if (!fin2.is_open()){
        cout << "Error opening file: " << testFile << endl;
        return 2;
    }
    fin2.close();

    
    if (argc == 4) {
        debugSet = true;
    }
    
    csvstream csvin(trainingFile);
    
    MVBNBC n1;
    
    if (debugSet) {
        n1.setDebug();
    }
    
    n1.training(csvin);
    
    if (debugSet) {
        n1.debugCode();
    }
    
    csvstream csvTest(testFile);
    
    n1.testing(csvTest);
}
