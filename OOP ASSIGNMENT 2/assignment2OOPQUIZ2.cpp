#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

// Abstract base class Exam
class Exam {
protected:
    std::string examID;
    std::string subject;
    int duration;

public:
    Exam(const std::string& id, const std::string& subj, int dur)
        : examID(id), subject(subj), duration(dur) {
        if (dur <= 0) {
            throw std::invalid_argument("Invalid exam duration");
        }
    }
    virtual ~Exam() {}
    virtual void gradeExam() const = 0;
    virtual void display() const {
        std::cout << "Exam ID: " << examID << ", Subject: " << subject << ", Duration: " << duration << " minutes";
    }
};
class MultipleChoiceExam : public Exam {
private:
    std::vector<std::pair<std::string, bool> > questions;

public:
    MultipleChoiceExam(const std::string& id, const std::string& subj, int dur, const std::vector<std::pair<std::string, bool> >& qs)
        : Exam(id, subj, dur), questions(qs) {}
        
    void gradeExam() const {
        int correctAnswers = 0;
        for (std::vector<std::pair<std::string, bool> >::const_iterator it = questions.begin(); it != questions.end(); ++it) {
            if (it->second) {
                ++correctAnswers;
            }
        }
        double score = (static_cast<double>(correctAnswers) / questions.size()) * 100;
        std::cout << "Multiple Choice Exam Score: " << score << "%" << std::endl;
    }

    void display() const {
        Exam::display();
        std::cout << ", Type: Multiple Choice Exam, Number of Questions: " << questions.size() << std::endl;
    }
};


class EssayExam : public Exam {
private:
    std::string topic;
    mutable double score;

public:
    EssayExam(const std::string& id, const std::string& subj, int dur, const std::string& tpc)
        : Exam(id, subj, dur), topic(tpc), score(0) {}
    void gradeExam() const {
        std::cout << "Enter the score for the essay exam: ";
        std::cin >> score;
        if (score < 0 || score > 100) {
            throw std::runtime_error("Invalid score. Score must be between 0 and 100.");
        }
        std::cout << "Essay Exam Score: " << score << "%" << std::endl;
    }
    void display() const {
        Exam::display();
        std::cout << ", Type: Essay Exam, Topic: " << topic << std::endl;
    }
};
class InvalidExamDurationException : public std::invalid_argument {
public:
    InvalidExamDurationException(const std::string& message)
        : std::invalid_argument(message) {}
};

class GradingErrorException : public std::runtime_error {
public:
    GradingErrorException(const std::string& message)
        : std::runtime_error(message) {}
};

int main() {
    std::srand(static_cast<unsigned int>(std::time(0)));
    try {
        std::vector<std::pair<std::string, bool> > mcQuestions;
        mcQuestions.push_back(std::make_pair("Question 1", true));
        mcQuestions.push_back(std::make_pair("Question 2", false));
        mcQuestions.push_back(std::make_pair("Question 3", true));
        mcQuestions.push_back(std::make_pair("Question 4", true));
        mcQuestions.push_back(std::make_pair("Question 5", false));
        
        MultipleChoiceExam mcExam("MC101", "Math", 60, mcQuestions);
        mcExam.display();
        mcExam.gradeExam();
        std::cout << std::endl;
        EssayExam essayExam("ESS101", "Literature", 120, "The impact of Shakespeare's works");
        essayExam.display();
        essayExam.gradeExam();
        std::cout << std::endl;
    } catch (const InvalidExamDurationException& ex) {
        std::cerr << "InvalidExamDurationException: " << ex.what() << std::endl;
    } catch (const GradingErrorException& ex) {
        std::cerr << "GradingErrorException: " << ex.what() << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }
    return 0;
}
