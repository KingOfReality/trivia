#include "SqliteDataBase.h"
#include <iostream>
#include <random>
#include <set>

int doesUserExistCallback(void* exist, int argc, char** argv, char** azColName) {
    if (argc > 0) {
        *reinterpret_cast<int*>(exist) = 1;
    }
    return 0;
}
bool SqliteDataBase::open()
{
    std::string dbFileName = "triviaDataBase.sqlite";
    int res = sqlite3_open(dbFileName.c_str(), &(this->db));
    if (res != SQLITE_OK)
    {
        std::cout << 111111111111;
        db = nullptr;
        return false;
    }
    return true;
}
int SqliteDataBase::createStatisticsTable() {
    std::string query = "CREATE TABLE IF NOT EXISTS statistics ("
        "userName TEXT PRIMARY KEY,"
        "averageAnswerTime REAL,"
        "numCorrectAnswers INTEGER,"
        "numTotalAnswers INTEGER,"
        "numPlayerGames INTEGER)";

    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error creating statistics table: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    return true;
}
bool SqliteDataBase::close()
{
    int rc = sqlite3_close(db);
    if (rc != SQLITE_OK) {
        return false;
    }
    return true;
}

int SqliteDataBase::doesUserExist(std::string str)
{
    int exist = 0;
    std::string sql = "SELECT * FROM User WHERE userName = '" + str + "'";
    sqlite3_exec(db, sql.c_str(), doesUserExistCallback, &exist, nullptr);
    return exist;
}

int SqliteDataBase::doesPasswordMatch(std::string pass, std::string passCon)
{
    int result = true;
    std::string query = "SELECT * FROM User WHERE userName = ? AND password = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, pass.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, passCon.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            result = false;
        }
        sqlite3_finalize(stmt);
    }
    std::cout << "result   " << result;
    return result;
}

int SqliteDataBase::addNewUser(std::string userName, std::string password, std::string email)
{
    int rc;
    sqlite3_stmt* stmt;

    std::string query = "INSERT INTO User (userName, password, email) VALUES (?, ?, ?)";

    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }

    sqlite3_bind_text(stmt, 3, userName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error inserting new user: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

std::list<Question> SqliteDataBase::getQuestions(int size)
{
    std::list<Question> questionList;

    std::string countQuery = "SELECT COUNT(*) FROM Questions";
    int numTotalQuestions = 0;

    // Execute the count query to get the total number of questions
    sqlite3_stmt* countStmt;
    if (sqlite3_prepare_v2(db, countQuery.c_str(), -1, &countStmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(countStmt) == SQLITE_ROW) {
            numTotalQuestions = sqlite3_column_int(countStmt, 0);
        }
        sqlite3_finalize(countStmt);
    }
    else {
        std::cerr << "Error executing SQL query: " << sqlite3_errmsg(db) << std::endl;
        return questionList;
    }

    if (size > numTotalQuestions) {
        std::cerr << "Requested size exceeds the total number of questions." << std::endl;
        return questionList;
    }

    std::vector<int> questionIndices;

    // Generate unique random indices
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, numTotalQuestions - 1);

    while (questionIndices.size() < size) {
        int randomIndex = dist(gen);
        if (std::find(questionIndices.begin(), questionIndices.end(), randomIndex) == questionIndices.end()) {
            questionIndices.push_back(randomIndex);
        }
    }

    std::string query = "SELECT * FROM Questions ORDER BY rowid";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        int counter = 0;

        while (sqlite3_step(stmt) == SQLITE_ROW && counter < numTotalQuestions) {
            if (std::find(questionIndices.begin(), questionIndices.end(), counter) != questionIndices.end()) {
                std::vector<std::string> question_answers;
                const char* questionText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                const char* answer1 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                const char* answer2 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
                const char* answer3 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
                const char* answer4 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
                int correctIndex = sqlite3_column_int(stmt, 5);

                question_answers.push_back(answer1);
                question_answers.push_back(answer2);
                question_answers.push_back(answer3);
                question_answers.push_back(answer4);
                Question question(question_answers, correctIndex, questionText);

                questionList.push_back(question);
            }

            counter++;

            if (questionList.size() >= size) {
                break;
            }
        }

        sqlite3_finalize(stmt);
    }
    else {
        std::cerr << "Error executing SQL query: " << sqlite3_errmsg(db) << std::endl;
    }


    return questionList;

}

float SqliteDataBase::getPlayerAvgAnswerTime(std::string name)
{
    return 0.0f;
}

int SqliteDataBase::getNumOfCorrectAnswers(std::string name)
{
    return 0;
}

int SqliteDataBase::getNumOfTotalAnswers(std::string name)
{
    return 0;
}

int SqliteDataBase::getNumOFPlayerGames(std::string name)
{
    return 0;
}
