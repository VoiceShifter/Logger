# pragma once
#ifndef LOGGER_HPP
#define LOGGER_HPP

# include <QObject>
# include <QDebug>
# include <QCoreApplication>


# include <iostream>
# include <fstream>
# include <cstring>
# include <vector>
# include <string>

static struct Colors
{
    const std::string RedColor{ "\033[0;31m" };
    const std::string YellowColor{ "\033[0;33m" };
    const std::string BlueColor{ "\033[0;36m" };
    const std::string Reset{ "\033[0m" };
} Colors;

enum class Items : size_t
{
    Month,
    Date,
    Year,
    Time,
    Hostname,
    LoggingLevel,
    ApplicationLevelNProccess,
    Message
};


class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);


    std::vector<std::vector<std::string>> Tokens;
    QStringList Items;
    signed int Amount;
    QStringList AllItems;



    void AnalyzeLog();
    void PrintSpecificLevel(char);
    void PrintTokensLine(size_t pLine);





    friend void PrintGreetings(Logger& Object);
    friend signed int TakeAction(Logger& Object);





    QStringList getItems() const;
    void setItems(const QStringList &newItems);
    void resetItems();



    void _PopulateItems(QStringList&);
    Q_INVOKABLE void const _PrintItems();
    Q_INVOKABLE void _PopulateItems();
    Q_INVOKABLE void _Constructor(const QString pLogFile);
    Q_INVOKABLE int _GetAmount();
    Q_INVOKABLE void _FilterChanged(signed int pFilter, bool pState);



    signed int getAmount() const;
    void setAmount(signed int newAmount);

    QStringList getAllItems() const;
    void setAllItems(const QStringList &newAllItems);

signals:
    void listPopulated();
    void AmountChanged();

    void AllItemsChanged();

private:
    Q_PROPERTY(QStringList _Items READ getItems WRITE setItems RESET resetItems NOTIFY listPopulated FINAL);
    Q_PROPERTY(signed int _Amount READ getAmount WRITE setAmount NOTIFY AmountChanged FINAL);

    std::fstream fLogFile;
    struct Statistic
    {
        size_t ErrorAmount;
        size_t WarningAmount;
        size_t InfoAmount;
        size_t CommonAmount;
    } fStatistic;
    char* fFileName{};
    std::vector<std::pair<char, bool>> fFilters{{'e', 1}, {'w', 1}, {'i', 1}}; //error warning info



    void FillVector(std::vector<std::string>& pVector);
    void TokenizeString(std::string&);
    void Update();

    void _TranslateToItems();


};

#endif // LOGGER_HPP
