#include "Logger.hpp"



void Logger::FillVector(std::vector<std::string>& pVector)
{
    std::string Buffer{};
    for (size_t Iterator{}; std::getline(fLogFile, Buffer); ++Iterator)
    {
        pVector.push_back(Buffer);
    }
}

inline void Logger::PrintTokensLine(size_t pLine)
{
    for (size_t Iterator{}; Iterator < Tokens[pLine].size(); ++Iterator)
    {
        if (Iterator == 5)
        {
            switch (Tokens[pLine][Iterator][0])
            {
            case 69:
                std::cout << Colors.RedColor;
                break;
            case 73:
                std::cout << Colors.BlueColor;
                break;
            case 87:
                std::cout << Colors.YellowColor;
                break;

            default:
                break;
            }
        }
        std::cout << Tokens[pLine][Iterator] << ' ' << Colors.Reset;
    }
    std::cout << '\n';
}

void Logger::AnalyzeLog()
{
    std::vector<std::string> Lines{};
    FillVector(Lines);

    Tokens.resize(Lines.size());

    for (size_t Iterator{}; Iterator < Lines.size(); ++Iterator)
    {
        char* Token{ std::strtok(const_cast<char*>(Lines[Iterator].c_str()), " ") };

        for (; Token != nullptr;)
        {
            Tokens[Iterator].push_back(Token);
            //std::cout << Token << " ";
            Token = std::strtok(nullptr, " ");
        }
        ++this->fStatistic.CommonAmount;
        switch (Tokens[Iterator][static_cast<size_t>(Items::LoggingLevel)][0])
        {
        case 69:
            ++this->fStatistic.ErrorAmount;
            break;

        case 87:
            ++this->fStatistic.WarningAmount;
            break;

        case 73:
            ++this->fStatistic.InfoAmount;
            break;

        default:
            std::cout << "Not mentioned log level found\n";
            break;
        }

        //std::cout << '\n';
    }
    //qDebug() << fStatistic.CommonAmount << "- Общее количество\n" << fStatistic.ErrorAmount << "Количетсво ощибок\n" << fStatistic.InfoAmount << "Количество информации";;

}

inline void Logger::PrintSpecificLevel(char pLevel)
{
    for (size_t Iterator{}; Iterator < Tokens.size(); ++Iterator)
    {
        if (Tokens[Iterator][static_cast<size_t>(Items::LoggingLevel)][0] == pLevel)
        {
            PrintTokensLine(Iterator);
        }
    }
}

void PrintOptions()
{
    std::cout << "Input: \n 1: To print only " << Colors.RedColor << "error's\n" << Colors.Reset;
    std::cout << " 2: To print only " << Colors.YellowColor << "warning's \n" << Colors.Reset;
    std::cout << " 3: To print only " << Colors.BlueColor << "info's\n" << Colors.Reset;
    std::cout <<  " 4: " << Colors.RedColor << "Reload file\n" << Colors.Reset;
    std::cout << " 0: Exiting\n ";
}


signed int TakeAction(Logger& Object)
{
    signed int Choice{};
    std::cin >> Choice;
    std::cin.clear();

    switch (Choice)
    {
    case 1:
        Object.PrintSpecificLevel('E');
        break;
    case 2:
        Object.PrintSpecificLevel('W');
        break;
    case 3:
        Object.PrintSpecificLevel('I');
        break;
    case 4:
        Object.Update();
        break;
    case 0:
        return 0;

    default:
        std::cout << "No such option\n";
        PrintOptions();
        break;
    }
    return 1;
}

void PrintGreetings(Logger& Object)
{

    std::cout << "LOGGER\n";
    for (size_t Iterator{}; Iterator < Object.Tokens.size(); ++Iterator)
    {
        Object.PrintTokensLine(Iterator);
    }
    std::cout << "\nPercent% of ERRORS'S - " << (Object.fStatistic.ErrorAmount / float(Object.fStatistic.CommonAmount)) * 100 << "%" << '\n';
    std::cout << "Percent% of WARNING'S - " << (Object.fStatistic.WarningAmount / float(Object.fStatistic.CommonAmount)) * 100 << "%" << '\n';
    std::cout << "Percent% of INFO'S - " << (Object.fStatistic.InfoAmount / float(Object.fStatistic.CommonAmount)) * 100 << "%" << '\n' << '\n';
    for (;;)
    {
        PrintOptions();
        if (TakeAction(Object) == 0)
        {
            std::cout << "Exiting...\n";
            break;
        }
    }
}

void Logger::Update()
{
    fLogFile.close();
    fLogFile.open(fFileName, std::ios::in);
    if (!fLogFile)
    {
        std::cout << "Something went wrong\n";
        return;
    }
    std::vector<std::string> Lines{};
    FillVector(Lines);
    std::cout << Lines.size() << " - size of new file\n" << Tokens.size() << " - current file size\n";

}


void Logger::TokenizeString(std::string& pString)
{
    char* Token{ std::strtok(const_cast<char*>(pString.c_str()), " ") };
    //Tokens.push_back(std::vector<std::string>());
    for (; Token != nullptr;)
    {


        //std::cout << Token << " ";
        Token = std::strtok(nullptr, " ");
    }
}



Logger::Logger(QObject *parent)
    : QObject{parent}
{


}

signed int Logger::getAmount() const
{

    return Amount;
}

void Logger::setAmount(signed int newAmount)
{
    if (Amount == newAmount)
        return;
    Amount = newAmount;
    emit AmountChanged();
}

QStringList Logger::getItems() const
{
    qDebug() << "Get Items called";
    return Items;
}

void Logger::setItems(const QStringList &newItems)
{
    Items.resize(Tokens.size());
    for (size_t Iterator{}; Iterator < Tokens.size(); ++Iterator)
    {
        for (size_t Inner{}; Inner < Tokens[Iterator].size(); ++Inner)
        {
            Items[Iterator] += Tokens[Iterator][Inner] + ' ';
        }
    }
    setAmount(Items.size());
    emit listPopulated();
}

void Logger::resetItems()
{
    setItems({}); // TODO: Adapt to use your actual default value
}

const void Logger::_PrintItems()
{
    for (size_t Iterator{}; Iterator < Items.size(); ++Iterator)
    {
        qDebug() << Items[Iterator];
    }
}

void Logger::_PopulateItems()
{

}

void Logger::_Constructor(const QString pLogFile)
{
    fLogFile.open(pLogFile.toStdString().c_str(), std::ios::in);
    fFileName = const_cast<char*>(pLogFile.toStdString().c_str());
    if (!fLogFile)
    {
        qDebug() << "No such file\n";
        return;
    }
    AnalyzeLog();
    _TranslateToItems();
}

int Logger::_GetAmount()
{
    qDebug() << Items.size();
    return Items.size();
}




void Logger::_TranslateToItems()
{
    Items.resize(Tokens.size());
    for (size_t Iterator{}; Iterator < Tokens.size(); ++Iterator)
    {
        for (size_t Inner{}; Inner < Tokens[Iterator].size(); ++Inner)
        {
            Items[Iterator] += Tokens[Iterator][Inner] + ' ';
        }
    }

    for (const auto& Iterator: Items)
    {
        qDebug() << Iterator;
    }
    emit listPopulated();
}

void Logger::_FilterChanged(signed int pFilter, bool pState)
{
    Items.clear();
    this->fStatistic = {};
    fFilters[pFilter].second = pState;


    for (size_t Iterator{}; Iterator < Tokens.size(); ++Iterator)
    {

        ++this->fStatistic.CommonAmount;
        switch (Tokens[Iterator][static_cast<size_t>(Items::LoggingLevel)][0])
        {
        case 69:
            if (fFilters[0].second)
            {
                ++this->fStatistic.ErrorAmount;
                for (size_t Inner{}; Inner < Tokens[Iterator].size(); ++Inner)
                {
                    Items[Iterator] += Tokens[Iterator][Inner] + ' ';
                }
            }
            break;

        case 87:
            if (fFilters[1].second)
            {
                ++this->fStatistic.WarningAmount;
                for (size_t Inner{}; Inner < Tokens[Iterator].size(); ++Inner)
                {
                    Items[Iterator] += Tokens[Iterator][Inner] + ' ';
                }
            }

            break;

        case 73:
            if (fFilters[1].second)
            {
                ++this->fStatistic.InfoAmount;
                for (size_t Inner{}; Inner < Tokens[Iterator].size(); ++Inner)
                {
                    Items[Iterator] += Tokens[Iterator][Inner] + ' ';
                }
            }

            break;

        default:
            std::cout << "Not mentioned log level found\n";
            break;
        }


    }
}
