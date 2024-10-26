#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <limits>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cctype>

using namespace std;

// Global Variables for Choises
bool Flag = false;
char Choice = 'Y';
int choice = 0;

const string RESET = "\033[0m";
const string GREEN = "\033[1;32m";  // [Success]  in green
const string RED = "\033[1;31m";    // [Error]   in red
const string YELLOW = "\033[1;33m"; // [Prompt]  in yellow
const string BLUE = "\033[34m";     // [Program Menu] in blue
const string CYAN = "\033[36m";     // Also Used for [Program Menu]

string validate(char Ch)
{
    if (Ch == 'D')
    { // D for validating Date
        string Expense_Date;
        bool isinvalid = true;
        cout << YELLOW << "[Prompt] " << RESET << " Enter Date in format (YYYY-MM-DD): ";
        while (isinvalid)
        {
            cin >> Expense_Date;
            if (Expense_Date.length() == 10 && Expense_Date[4] == '-' && Expense_Date[7] == '-')
            {
                try
                {
                    int year = stoi(Expense_Date.substr(0, 4));
                    int month = stoi(Expense_Date.substr(5, 2));
                    int day = stoi(Expense_Date.substr(8, 2));

                    if (year > 1900 && year < 2100 && month > 0 && month < 13 && day > 0 && day < 32)
                    {
                        bool validDay = true;
                        if (month == 2)
                        { // Checking for February
                            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                            {
                                if (day > 29)
                                    validDay = false;
                            }
                            else
                            {
                                if (day > 28)
                                    validDay = false;
                            }
                        }
                        else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
                        {
                            validDay = false;
                        }

                        if (validDay)
                        {
                            isinvalid = false; // Valid date
                        }
                        else
                        {
                            cout << RED << "[Error]  " << RESET << " Invalid day for the given month and year. Please enter a valid date." << endl;
                        }
                    }
                    else
                    {
                        cout << RED << "[Error] " << RESET << " Invalid date. Please enter a date in the format YYYY-MM-DD." << endl;
                    }
                }
                catch (const invalid_argument &)
                {
                    cout << RED << "[Error] " << RESET << " Invalid date format. Please enter the date in the format YYYY-MM-DD." << endl;
                }
                catch (const out_of_range &)
                {
                    cout << RED << "[Error] " << RESET << " Date out of range. Please enter a valid date." << endl;
                }
            }
            else
            {
                cout << RED << "[Error] " << RESET << " Invalid date format. Please enter the date in the format YYYY-MM-DD." << endl;
            }
        }
        return Expense_Date;
    }

    else if (Ch == 'E')
    { // E for validating Email
        string Email;
        bool isinvalid = true;
        bool hasdot = false;
        bool hasamp = false;
        int ampindex = -1;

        while (isinvalid)
        {
            cout << YELLOW << "[Prompt]" << RESET << " Enter your Email: ";
            cin.ignore(); // Clear buffer
            getline(cin, Email);

            hasdot = false;
            hasamp = false;
            ampindex = -1;
            isinvalid = false;

            for (int i = 0; i < Email.size(); i++)
            {
                if (Email[i] == ' ')
                {
                    cout << RED << "[Error] " << RESET << " Invalid Email Format. No spaces are allowed in an email. Please Re-Enter!" << endl;
                    isinvalid = true;
                    break;
                }

                if (!((Email[i] >= 'A' && Email[i] <= 'Z') || (Email[i] >= 'a' && Email[i] <= 'z') ||
                      (Email[i] >= '0' && Email[i] <= '9') || Email[i] == '_' ||
                      Email[i] == '-' || Email[i] == '.' || Email[i] == '@'))
                {
                    cout << RED << "[Error] " << RESET << " Invalid Email Format. Only alphanumeric characters, underscores (_), hyphens (-), dots (.), and '@' are allowed." << endl;
                    isinvalid = true;
                    break;
                }

                if (Email[i] == '@')
                {
                    if (ampindex == -1)
                    {
                        ampindex = i;
                        hasamp = true;
                    }
                    else
                    {
                        cout << RED << "[Error]" << RESET << " Invalid Email Format. Only one '@' is allowed in an email address." << endl;
                        isinvalid = true;
                        break;
                    }
                }

                if (ampindex != -1 && Email[i] == '.')
                {
                    hasdot = true;
                }
            }

            if (!hasamp)
            {
                cout << RED << "[Error] " << RESET << " Invalid Email Format. The email must contain an '@' symbol." << endl;
                isinvalid = true;
            }
            else if (!hasdot || ampindex >= Email.size() - 3)
            {
                cout << RED << "[Error] " << RESET << " Invalid Email Format. The domain part must contain a dot (e.g., '.com', '.org')." << endl;
                isinvalid = true;
            }
        }

        cout << GREEN << "[Success] " << RESET << " Valid Email entered!" << endl;
        return Email;
    }

    else if (Ch == 'U')
    { // U for Username Validation
        string Username;
        bool isinvalid = true;
        cout << YELLOW << "[Prompt]" << RESET << " Enter your Username: ";
        while (isinvalid)
        {
            cin >> Username;
            isinvalid = false;

            if (Username.length() < 5 || Username.length() > 15)
            {
                cout << RED << "[Error] " << RESET << " Invalid Username. It must be between 5 and 15 characters long." << endl;
                isinvalid = true;
            }

            for (int i = 0; i < Username.size(); i++)
            {
                if (!((Username[i] >= 'A' && Username[i] <= 'Z') || (Username[i] >= 'a' && Username[i] <= 'z') ||
                      (Username[i] >= '0' && Username[i] <= '9') || Username[i] == '_' || Username[i] == '.'))
                {
                    cout << RED << "[Error] " << RESET << " Invalid Username. Only alphanumeric characters, underscores (_), and dots (.) are allowed." << endl;
                    isinvalid = true;
                    break;
                }
            }
        }
        return Username;
    }

    else if (Ch == 'P')
    { // P for Password Validation
        string Password;
        bool isinvalid = true;
        cout << YELLOW << "[Prompt]" << RESET << " Enter your Password: ";
        while (isinvalid)
        {
            cin >> Password;
            isinvalid = false;

            if (Password.length() < 8)
            {
                cout << RED << "[Error] " << RESET << " Invalid Password. It must be at least 8 characters long." << endl;
                isinvalid = true;
                continue;
            }

            bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
            for (char c : Password)
            {
                if (isupper(c))
                    hasUpper = true;
                else if (islower(c))
                    hasLower = true;
                else if (isdigit(c))
                    hasDigit = true;
                else if (ispunct(c))
                    hasSpecial = true;
            }

            if (!hasUpper || !hasLower || !hasDigit || !hasSpecial)
            {
                cout << RED << "[Error] " << RESET << " Invalid Password. It must contain at least one uppercase letter, one lowercase letter, one digit, and one special character." << endl;
                isinvalid = true;
            }
        }
        return Password;
    }

    return "";
}

void SortVec(vector<string> &names, vector<string> &dates, vector<double> &amounts, char ch)
{
    // Create a vector of indices
    vector<int> indices(names.size());
    for (int i = 0; i < names.size(); i++)
    {
        indices[i] = i;
    }

    // Sorting logic
    if (ch == 'A') // Sort By Names
    {
        int order;
        cout << YELLOW << "[Prompt]  " << RESET << " Enter 1 to sort Expenses in Ascending Order of Names" << endl;
        cout << YELLOW << "[Prompt]  " << RESET << " Enter 2 to sort Expenses in Descending Order of Names" << endl;
        while (true)
        {
            cin >> order;
            if (order == 1 || order == 2)
            {
                bool ascending = (order == 1);
                sort(indices.begin(), indices.end(), [ascending, &names](int i1, int i2)
                     { return ascending ? names[i1] < names[i2] : names[i1] > names[i2]; });
                break;
            }
            else
            {
                cout << RED << "[Error] " << RESET << " Invalid Number. Enter 1 or 2 only" << endl;
            }
        }
    }
    else if (ch == 'B') // Sort By Amount
    {
        int order;
        cout << YELLOW << "[Prompt]  " << RESET << " Enter 1 to sort Expenses in Ascending Order of Amounts" << endl;
        cout << YELLOW << "[Prompt] " << RESET << " Enter 2 to sort Expenses in Descending Order of Amounts" << endl;
        while (true)
        {
            cin >> order;
            if (order == 1 || order == 2)
            {
                bool ascending = (order == 1);
                sort(indices.begin(), indices.end(), [ascending, &amounts](int i1, int i2)
                     { return ascending ? amounts[i1] < amounts[i2] : amounts[i1] > amounts[i2]; });
                break;
            }
            else
            {
                cout << RED << "[Error] " << RESET << " Invalid Number. Enter 1 or 2 only" << endl;
            }
        }
    }
    else // Sort by Dates
    {
        int order;
        cout << YELLOW << "[Prompt] " << RESET << " Enter 1 to sort Expenses in Ascending Order of Dates" << endl;
        cout << YELLOW << "[Prompt] " << RESET << " Enter 2 to sort Expenses in Descending Order of Dates" << endl;
        while (true)
        {
            cin >> order;
            if (order == 1 || order == 2)
            {
                bool ascending = (order == 1);
                sort(indices.begin(), indices.end(), [ascending, &dates](int i1, int i2)
                     { return ascending ? dates[i1] < dates[i2] : dates[i1] > dates[i2]; });
                break;
            }
            else
            {
                cout << RED << "[Error] " << RESET << " Invalid Number. Enter 1 or 2 only" << endl;
            }
        }
    }

    // Reorder the vectors based on sorted indices
    vector<string> sortedNames(names.size());
    vector<string> sortedDates(dates.size());
    vector<double> sortedAmounts(amounts.size());

    for (int i = 0; i < indices.size(); i++)
    {
        sortedNames[i] = names[indices[i]];
        sortedDates[i] = dates[indices[i]];
        sortedAmounts[i] = amounts[indices[i]];
    }

    names = sortedNames;
    dates = sortedDates;
    amounts = sortedAmounts;
}

void Displayvec(const vector<string> &names, const vector<string> &dates, const vector<double> &amounts)
{
    cout << "+" << string(65, '-') << "+" << endl;
    cout << "| " << left << setw(28) << "Attribute Name"
         << "| " << setw(13) << "Date"
         << "| " << right << setw(15) << "Amount " << "|" << endl;
    cout << "+" << string(65, '-') << "+" << endl;

    for (int i = 0; i < names.size(); ++i)
    {
        cout << "| " << left << setw(28) << names[i]
             << "| " << setw(13) << dates[i]
             << "| " << right << setw(14) << fixed << setprecision(2) << amounts[i] << " |" << endl;
    }
    cout << "+" << string(65, '-') << "+" << endl;
}
void RecordVec(vector<string> &names, vector<string> &dates, vector<double> &amounts)
{
    char Choice = 'Y';
    while (Choice == 'Y' || Choice == 'y')
    {
        double stream_amount;
        string stream_name;
        string stream_date;
        cout << YELLOW << "[Prompt] " << RESET << " Enter the name of the stream: ";
        cin.ignore();
        getline(cin, stream_name);
        stream_date = validate('D');
        cout << YELLOW << "[Prompt] " << RESET << " Enter Amount generated / Used by " << stream_name << ": ";

        while (!(cin >> stream_amount))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "[Error] " << RESET << " Invalid input. Please enter a numeric value for the amount: ";
        }
        names.push_back(stream_name);
        amounts.push_back(stream_amount);
        dates.push_back(stream_date);
        cout << YELLOW << "[Prompt] " << RESET << " Do you want to add another income stream? (Y for yes, N for no): ";
        cin >> Choice;
        while (Choice != 'Y' && Choice != 'y' && Choice != 'N' && Choice != 'n')
        {
            cout << RED << "[Error] " << RESET << " Invalid Input. Please Enter Y for yes or N for no." << endl;
            cin >> Choice;
        }
    }
}

void ModifyVec(vector<string> &names, vector<string> &dates, vector<double> &amounts)
{
    char Choice = 'Y';
    while (Choice == 'Y' || Choice == 'y')
    {
        cout << YELLOW << "[Prompt] " << RESET << "\nDo you want to add, delete, or modify a vector\n";
        cout << "1. Add\n2. Delete\n3. Modify\n4. Exit\n";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1: // Add another One
        {
            double amt;
            string name, date;
            cout << YELLOW << "[Prompt] " << RESET << " Enter Name: ";
            cin.ignore();
            getline(cin, name);
            date = validate('D');
            cout << YELLOW << "[Prompt] " << RESET << " Enter Amount: ";
            while (!(cin >> amt))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << RED << "[Error] " << RESET << " Invalid input. Please enter a numeric value for the amount: ";
            }
            names.push_back(name);
            dates.push_back(date);
            amounts.push_back(amt);
        }
        break;

        case 2: // Delete an existing one
        {
            int index;
            cout << YELLOW << "[Prompt] " << RESET << "Which Income Stream do you want to delete (Enter Index): ";
            cin >> index;
            if (index >= 0 && index < names.size())
            {
                names.erase(names.begin() + index);
                dates.erase(dates.begin() + index);
                amounts.erase(amounts.begin() + index);
                cout << GREEN << "[Success] " << RESET << "Entry deleted successfully.\n";
            }
            else
                cout << RED << "[Error] " << RESET << "Invalid Index.\n";
        }
        break;

        case 3: // Modify an existing one
        {
            int index;
            cout << YELLOW << "[Prompt] " << RESET << "Which Vector do you want to modify (Enter Index): ";
            cin >> index;
            if (index >= 0 && index < names.size())
            {
                string name;
                double amt;
                string date;

                cout << YELLOW << "[Prompt] " << RESET << "Enter New Name: ";
                cin.ignore();
                getline(cin, name);
                cout << YELLOW << "[Prompt] " << RESET << "Enter New Amount: ";
                while (!(cin >> amt))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << RED << "[Error] " << RESET << "Invalid Input. Please enter a numeric value for the amount: ";
                }
                date = validate('D');
                names[index] = name;
                dates[index] = date;
                amounts[index] = amt;
                cout << GREEN << "[Success] " << RESET << "Entry modified successfully.\n";
            }
            else
                cout << RED << "[Error] " << RESET << "Invalid Index.\n";
        }
        break;

        case 4: // Exit
            cout << GREEN << "[Success] " << RESET << "Exiting modification menu.\n";
            return;

        default:
            cout << RED << "[Error] " << RESET << " Invalid Choice. Please enter 1, 2, 3, or 4.\n";
            break;
        }

        cout << YELLOW << "[Prompt] " << RESET << "Do you want to continue? (Y/N): ";
        cin >> Choice;
    }
}

void Operations(const vector<string> &itemNames, const vector<string> &itemDates, const vector<double> &itemAmounts)
{
    if (itemAmounts.empty())
    {
        cout << RED << "[Error] " << RESET << "No records found.\n";
        return;
    }

    double highestAmount = 0;
    double lowestAmount = numeric_limits<double>::max();
    double totalAmount = 0;
    string highestItemName, lowestItemName;
    string highestItemDate, lowestItemDate;

    for (int i = 0; i < itemNames.size(); ++i)
    {
        if (itemAmounts[i] > highestAmount)
        {
            highestAmount = itemAmounts[i];
            highestItemName = itemNames[i];
            highestItemDate = itemDates[i];
        }
        if (itemAmounts[i] < lowestAmount)
        {
            lowestAmount = itemAmounts[i];
            lowestItemName = itemNames[i];
            lowestItemDate = itemDates[i];
        }
        totalAmount += itemAmounts[i];
    }

    cout << "\n"
         << GREEN << "[Success] " << RESET << " Summary of Financial Records:\n";
    cout << string(40, '-') << endl;

    cout << left << setw(30) << "Highest Record:"
         << right << setw(10) << highestItemName << endl;
    cout << left << setw(30) << "Amount:"
         << right << setw(10) << fixed << setprecision(2) << highestAmount << endl;
    cout << left << setw(30) << "Date:"
         << right << setw(10) << highestItemDate << endl;

    cout << left << setw(30) << "Lowest Record:"
         << right << setw(10) << lowestItemName << endl;
    cout << left << setw(30) << "Amount:"
         << right << setw(10) << fixed << setprecision(2) << lowestAmount << endl;
    cout << left << setw(30) << "Date:"
         << right << setw(10) << lowestItemDate << endl;

    cout << left << setw(30) << "Total Amount:"
         << right << setw(10) << fixed << setprecision(2) << totalAmount << endl;
}
class Income;

class PassiveIncome
{
    vector<double> Passive_income_stream_Amount;
    vector<string> Passive_income_stream_names;
    vector<string> Passive_income_stream_date;

public:
    void RecordPassiveIncome()
    {
        RecordVec(Passive_income_stream_names, Passive_income_stream_date, Passive_income_stream_Amount);
    }

    void DisplayPassiveIncome()
    {
        Displayvec(Passive_income_stream_names, Passive_income_stream_date, Passive_income_stream_Amount);
    }

    void ModifyPassiveIncome()
    {
        ModifyVec(Passive_income_stream_names, Passive_income_stream_date, Passive_income_stream_Amount);
    }

    void OperationOnPassiveIncome()
    {
        Operations(Passive_income_stream_names, Passive_income_stream_date, Passive_income_stream_Amount);
    }

    void Reset()
    {
        Passive_income_stream_Amount.clear();
        Passive_income_stream_names.clear();
        Passive_income_stream_date.clear();
        cout << GREEN << "[Sucess]" << RESET << " Passive Income streams reseted succesfully." << endl;
    }

    friend class Income;
    friend class FinanceHub;
    friend class User;
};

class ActiveIncome
{
    vector<double> Active_income_stream_Amount;
    vector<string> Active_income_stream_names;
    vector<string> Active_incom_stream_date;

public:
    void RecordActiveIncome()
    {
        RecordVec(Active_income_stream_names, Active_incom_stream_date, Active_income_stream_Amount);
    }

    void DisplayActiveIncome() const
    {
        Displayvec(Active_income_stream_names, Active_incom_stream_date, Active_income_stream_Amount);
    }

    void ModifyActiveIncome()
    {
        ModifyVec(Active_income_stream_names, Active_incom_stream_date, Active_income_stream_Amount);
    }

    void OperationOnActiveIncome()
    {
        Operations(Active_income_stream_names, Active_incom_stream_date, Active_income_stream_Amount);
    }

    void Reset()
    {
        Active_income_stream_Amount.clear();
        Active_income_stream_names.clear();
        Active_incom_stream_date.clear();
        cout << GREEN << "[Sucess]" << RESET << " Active Income streams reseted succesfully." << endl;
    }

    friend class Income;
    friend class FinanceHub;
    friend class User;
};

class Income
{
    PassiveIncome Pa;
    ActiveIncome Ac;

    double amt = 0;
    double tax;

public:
    void CopyPassiveIncome(const PassiveIncome &pi)
    {
        if (pi.Passive_income_stream_Amount.empty())
            cerr << RED << "[Error] " << RESET << " Please Enter Some Passive Income Streams" << endl;
        else
            Pa = pi;
    }

    void CopyActiveIncome(const ActiveIncome &ai)
    {
        if (ai.Active_incom_stream_date.empty())
            cerr << RED << "[Error] " << RESET << " Please Enter Some Active Income Streams" << endl;
        else
            Ac = ai;
    }
    int returntaxes() { return tax; }
    void CalculateTaxes(char Display)
    {
        tax = 0;
        amt = 0;
        /*
        According to the new tax regime of India as of 08 Sep 2024:

        1. Income up to ₹3,00,000: No tax
        2. Income from ₹3,00,001 to ₹6,00,000: 5% of income exceeding ₹3,00,000
        3. Income from ₹6,00,001 to ₹9,00,000: 10% of income exceeding ₹6,00,000 + ₹15,000
        4. Income from ₹9,00,001 to ₹12,00,000: 15% of income exceeding ₹9,00,000 + ₹45,000
        5. Income from ₹12,00,001 to ₹15,00,000: 20% of income exceeding ₹12,00,000 + ₹90,000
        6. Income above ₹15,00,000: 30% of income exceeding ₹15,00,000 + ₹1,80,000
        */

        for (int i = 0; i < Pa.Passive_income_stream_names.size(); i++)
        {
            amt += Pa.Passive_income_stream_Amount[i];
        }
        for (int i = 0; i < Ac.Active_income_stream_names.size(); i++)
        {
            amt += Ac.Active_income_stream_Amount[i];
        }

        if (amt > 1500000)
        {
            tax = (amt - 1500000) * 0.30 + 180000;
        }
        else if (amt > 1200000)
        {
            tax = (amt - 1200000) * 0.20 + 90000;
        }
        else if (amt > 900000)
        {
            tax = (amt - 900000) * 0.15 + 45000;
        }
        else if (amt > 600000)
        {
            tax = (amt - 600000) * 0.10 + 15000;
        }
        else if (amt > 300000)
        {
            tax = (amt - 300000) * 0.05;
        }
        if (Display == 'Y')
        {
            double TotalIncome = amt - tax;
            cout << "\n"
                 << GREEN << "[Success] " << RESET << " Income and Tax Summary:\n";
            cout << string(40, '-') << endl;
            cout << left << setw(30) << "Total Income:"
                 << right << setw(10) << fixed << setprecision(2) << TotalIncome << endl;
            cout << left << setw(30) << "Total Taxes:"
                 << right << setw(10) << fixed << setprecision(2) << tax << endl;
            cout << string(40, '-') << endl;
        }
    }

    void Sort()
    {
        bool isvalidInput = false;
        cout << YELLOW << "[Prompt] " << RESET << " Which Income Stream Do you want to sort" << endl;
        cout << "1. Passive Income" << endl;
        cout << "2. Active Income" << endl;
        while (!isvalidInput)
        {
            cin >> choice;
            if (choice == 1 || choice == 2)
                isvalidInput = true;
            else
                cout << RED << "[Error] " << RESET << " Invalid Choice. Choose 1 or 2 only" << endl;
        }

        if (choice == 1)
        {
            if (Pa.Passive_income_stream_Amount.empty() || Pa.Passive_income_stream_names.empty())
            {
                cout << RED << "[Error] " << RESET << " No income streams to sort." << endl;
                cout << YELLOW << "[Prompt] " << RESET << " Please Enter Some streams to sort" << endl;
            }
            else
            {
                bool isValid = false;
                cout << YELLOW << "[Prompt] " << RESET << " By which Metric to sort Passive Income Streams" << endl;
                cout << "A By Name" << endl;
                cout << "B By Amount" << endl;
                cout << "C By Date" << endl;
                while (!isValid)
                {
                    cin >> Choice;
                    if (Choice == 'A' || Choice == 'B' || Choice == 'C')
                    {
                        isValid = true;
                    }
                    else
                    {
                        cout << RED << "[Error] " << RESET << " Invalid choice. Please enter A, B, or C." << endl;
                    }
                }
                SortVec(Pa.Passive_income_stream_names, Pa.Passive_income_stream_date, Pa.Passive_income_stream_Amount, Choice);
                cout << GREEN << "[Success] " << RESET << " After Sorting" << endl;
                Display('P');
            }
        }

        else if (choice == 2)
        {
            if (Ac.Active_income_stream_Amount.empty() || Ac.Active_income_stream_names.empty())
            {
                cout << RED << "[Error] " << RESET << "No income streams to sort." << endl;
                cout << YELLOW << "[Prompt] " << RESET << "Please Enter Some streams to sort" << endl;
            }
            else
            {
                bool isValid = false;
                cout << YELLOW << "[Prompt] " << RESET << "By which Metric to sort Passive Income Streams" << endl;
                cout << "A By Name" << endl;
                cout << "B By Amount" << endl;
                cout << "C By Date" << endl;
                while (!isValid)
                {
                    cin >> Choice;
                    if (Choice == 'A' || Choice == 'B' || Choice == 'C')
                    {
                        isValid = true; // Exit the loop if input is valid
                    }
                    else
                    {
                        cout << RED << "[Error] " << RESET << "Invalid choice. Please enter A, B, C, or D." << endl;
                    }
                }
                SortVec(Ac.Active_income_stream_names, Ac.Active_incom_stream_date, Ac.Active_income_stream_Amount, Choice);
                cout << GREEN << "[Success] " << RESET << "After Sorting" << endl;
                Display('A');
            }
        }
    }
    void Display(char ch)
    { // For Income Streams
        if (ch == 'A')
        { // Display Active Income
            if (Ac.Active_income_stream_Amount.empty())
            {
                cout << RED << "[Error] " << RESET << "No Active Income streams recorded." << endl;
                return;
            }
            cout << GREEN << "[Success] " << RESET << " Active Income Streams:" << endl;
            cout << "+" << string(65, '-') << "+" << endl;
            cout << "| " << left << setw(28) << "Active Income Stream"
                 << "| " << setw(13) << "Date"
                 << "| " << right << setw(15) << "Amount " << "|" << endl;
            cout << "+" << string(65, '-') << "+" << endl;

            for (int i = 0; i < Ac.Active_income_stream_Amount.size(); ++i)
            {
                cout << "| " << left << setw(28) << Ac.Active_income_stream_names[i]
                     << "| " << setw(13) << Ac.Active_incom_stream_date[i]
                     << "| " << right << setw(14) << fixed << setprecision(2) << Ac.Active_income_stream_Amount[i] << " |" << endl;
            }
            cout << "+" << string(65, '-') << "+" << endl;
        }
        else if (ch == 'P')
        { // Display Passive Income
            if (Pa.Passive_income_stream_Amount.empty())
            {
                cout << RED << "[Error] " << RESET << "No Passive Income streams recorded." << endl;
                return;
            }
            cout << GREEN << "[Success] " << RESET << " Passive Income Streams:" << endl;
            cout << "+" << string(65, '-') << "+" << endl;
            cout << "| " << left << setw(28) << "Passive Income Stream"
                 << "| " << setw(13) << "Date"
                 << "| " << right << setw(15) << "Amount " << "|" << endl;
            cout << "+" << string(65, '-') << "+" << endl;

            for (int i = 0; i < Pa.Passive_income_stream_Amount.size(); ++i)
            {
                cout << "| " << left << setw(28) << Pa.Passive_income_stream_names[i]
                     << "| " << setw(13) << Pa.Passive_income_stream_date[i]
                     << "| " << right << setw(14) << fixed << setprecision(2) << Pa.Passive_income_stream_Amount[i] << " |" << endl;
            }
            cout << "+" << string(65, '-') << "+" << endl;
        }
    }

    void GenerateReport() const
    {
        ofstream reportFile("IncomeReport.txt");

        if (!reportFile.is_open())
        {
            cerr << RED << "[Error] " << RESET << "Error: Could not open file for writing." << endl;
            return;
        }

        reportFile << "============================ Income Report ============================\n";
        reportFile << "\nPassive Income Streams:\n";
        reportFile << left << setw(25) << "Income Stream" << right << setw(15) << "Amount Generated" << endl;
        reportFile << string(40, '-') << endl;

        for (int i = 0; i < Pa.Passive_income_stream_names.size(); ++i)
        {
            reportFile << left << setw(25) << Pa.Passive_income_stream_names[i]
                       << right << setw(15) << fixed << setprecision(2) << Pa.Passive_income_stream_Amount[i] << endl;
        }

        reportFile << "\nActive Income Streams:\n";
        reportFile << left << setw(25) << "Income Stream" << right << setw(15) << "Amount Generated" << endl;
        reportFile << string(40, '-') << endl;

        for (int i = 0; i < Ac.Active_income_stream_names.size(); ++i)
        {
            reportFile << left << setw(25) << Ac.Active_income_stream_names[i]
                       << right << setw(15) << fixed << setprecision(2) << Ac.Active_income_stream_Amount[i] << endl;
        }

        reportFile << "\nSummary:\n";
        reportFile << string(40, '-') << endl;
        reportFile << left << setw(30) << "Total Income:" << right << setw(10) << fixed << setprecision(2) << amt << endl;
        reportFile << left << setw(30) << "Total Taxes:" << right << setw(10) << fixed << setprecision(2) << tax << endl;
        reportFile << string(40, '-') << endl;

        reportFile.close();
        cout << GREEN << "[Success] " << RESET << " Income report generated successfully." << endl;
    }

    void Reset()
    {
        amt = 0;
        tax = 0;
        Pa.Reset();
        Ac.Reset();
    }

    void Commit(PassiveIncome &p, ActiveIncome &a)
    {
        bool committed = false;

        if (!Pa.Passive_income_stream_Amount.empty())
        {
            p = Pa;
            committed = true;
        }

        if (!Ac.Active_income_stream_Amount.empty())
        {
            a = Ac;
            committed = true;
        }

        if (committed)
        {
            cout << GREEN << "[Success] " << RESET << " Income data committed successfully." << endl;
        }
        else
        {
            cout << YELLOW << "[Warning]" << RESET << " No data to commit. Both Passive and Active income streams are empty." << endl;
        }
    }

    friend class FinanceHub;
    friend class User;
};

class FixedExpenditure
{
    vector<double> Fixed_Expenditure_Amount;
    vector<string> Fixed_Expenditure_Name;
    vector<string> Fixed_Expenditure_Date;

public:
    void RecordFixedExpenditure()
    {
        RecordVec(Fixed_Expenditure_Name, Fixed_Expenditure_Date, Fixed_Expenditure_Amount);
    }

    void DisplayFixedExpenditures()
    {
        Displayvec(Fixed_Expenditure_Name, Fixed_Expenditure_Date, Fixed_Expenditure_Amount);
    }

    void ModifyFixedExpenditure()
    {
        ModifyVec(Fixed_Expenditure_Name, Fixed_Expenditure_Date, Fixed_Expenditure_Amount);
    }

    void OperationsOnFixedExpenditure()
    {
        Operations(Fixed_Expenditure_Name, Fixed_Expenditure_Date, Fixed_Expenditure_Amount);
    }

    void Reset()
    {
        Fixed_Expenditure_Amount.clear();
        Fixed_Expenditure_Name.clear();
        Fixed_Expenditure_Date.clear();
        cout << GREEN << "[Sucess]" << RESET << " Fixed Expense streams reseted succesfully." << endl;
    }

    friend class Expenditure;
    friend class Budget;
    friend class FinanceHub;
    friend class User;
};

class VariableExpenditure
{
    vector<double> Variable_Expenditure_Amount;
    vector<string> Variable_Expenditure_Name;
    vector<string> Variable_Expenditure_Date;

public:
    void RecordVariableExpenditure()
    {
        RecordVec(Variable_Expenditure_Name, Variable_Expenditure_Date, Variable_Expenditure_Amount);
    }

    void DisplayVariableExpenditures() const
    {
        Displayvec(Variable_Expenditure_Name, Variable_Expenditure_Date, Variable_Expenditure_Amount);
    }

    void ModifyVariableExpenditure()
    {
        ModifyVec(Variable_Expenditure_Name, Variable_Expenditure_Date, Variable_Expenditure_Amount);
    }

    void OperationsOnVariableExpenditure() const
    {
        Operations(Variable_Expenditure_Name, Variable_Expenditure_Date, Variable_Expenditure_Amount);
    }

    void Reset()
    {
        Variable_Expenditure_Amount.clear();
        Variable_Expenditure_Name.clear();
        Variable_Expenditure_Date.clear();
        cout << GREEN << "[Sucess]" << RESET << " Variable Expense streams reseted succesfully." << endl;
    }

    friend class Expenditure;
    friend class Budget;
    friend class FinanceHub;
    friend class User;
};

class Expenditure
{
    FixedExpenditure Fe;
    VariableExpenditure Ve;

    double total_expenditure = 0;

public:
    void CopyFixedExpenditure(const FixedExpenditure &fe)
    {
        if (fe.Fixed_Expenditure_Amount.empty())
            cerr << RED << "[Error] " << RESET << " Please Enter some Fixed Expenses First." << endl;
        else
            Fe = fe;
    }

    void CopyVariableExpenditure(const VariableExpenditure &ve)
    {
        if (ve.Variable_Expenditure_Name.empty())
            cerr << RED << "[Error] " << RESET << " Please Enter some Variable Expenses first." << endl;
        else
            Ve = ve;
    }

    double CalculateTotalExpenditure(char choice)
    {
        double total_expenditure = 0;

        // Calculate total expenditure
        for (const auto &amount : Fe.Fixed_Expenditure_Amount)
        {
            total_expenditure += amount;
        }
        for (const auto &amount : Ve.Variable_Expenditure_Amount)
        {
            total_expenditure += amount;
        }

        if (choice == 'Y')
        {
            const int width = 65;
            cout << "+" << string(width, '-') << "+\n";
            cout << "| " << left << setw(28) << "Attribute Name"
                 << "| " << setw(13) << "Date"
                 << "| " << right << setw(15) << "Amount |" << endl;
            cout << "+" << string(width, '-') << "+\n";

            // Display Fixed Expenditures
            for (int i = 0; i < Fe.Fixed_Expenditure_Amount.size(); ++i)
            {
                cout << "| " << left << setw(28) << Fe.Fixed_Expenditure_Name[i]
                     << "| " << setw(13) << Fe.Fixed_Expenditure_Date[i]
                     << "| " << right << setw(14) << fixed << setprecision(2)
                     << Fe.Fixed_Expenditure_Amount[i] << " |" << endl;
            }

            // Display Variable Expenditures
            for (int i = 0; i < Ve.Variable_Expenditure_Amount.size(); ++i)
            {
                cout << "| " << left << setw(28) << Ve.Variable_Expenditure_Name[i]
                     << "| " << setw(13) << Ve.Variable_Expenditure_Date[i]
                     << "| " << right << setw(14) << fixed << setprecision(2)
                     << Ve.Variable_Expenditure_Amount[i] << " |" << endl;
            }

            cout << "+" << string(width, '-') << "+\n";
            cout << "| " << left << setw(44) << "Total Expenditure:"
                 << "| " << right << setw(14) << fixed << setprecision(2)
                 << total_expenditure << " |" << endl;
            cout << "+" << string(width, '-') << "+\n";
        }
        else
        {
            return total_expenditure;
        }
    }
    void Sort()
    {
        Flag = false;
        cout << YELLOW << "[Prompt] " << RESET << " Which type of Expense Do you Want to sort?" << endl;
        cout << "1.) Fixed Expenses" << endl;
        cout << "2.) Variable Expenses" << endl;

        while (!Flag)
        {
            cin >> choice;
            if (choice == 1 || choice == 2)
                Flag = true;
            else
                cout << RED << "[Error] " << RESET << " Invalid Choice. Choose 1 or 2 only." << endl;
        }

        Flag = false; // Reset flag for next use

        if (choice == 1)
        {
            if (Fe.Fixed_Expenditure_Amount.empty() || Fe.Fixed_Expenditure_Date.empty() || Fe.Fixed_Expenditure_Name.empty())
            {
                cout << RED << "[Error] " << RESET << " No Fixed Expenses to sort." << endl;
                cout << YELLOW << "[Prompt] " << RESET << " Please Enter Some expenses to sort." << endl;
            }
            else
            {
                cout << YELLOW << "[Prompt] " << RESET << " By which Metric do you want to sort Fixed Expenses?" << endl;
                cout << "A by Name" << endl;
                cout << "B by Amount" << endl;
                cout << "C by Date" << endl;

                while (!Flag)
                {
                    cin >> Choice;
                    if (Choice == 'A' || Choice == 'B' || Choice == 'C')
                    {
                        Flag = true;
                    }
                    else
                    {
                        cout << RED << "[Error] " << RESET << " Invalid Choice. Please Enter A, B, or C." << endl;
                    }
                }

                SortVec(Fe.Fixed_Expenditure_Name, Fe.Fixed_Expenditure_Date, Fe.Fixed_Expenditure_Amount, Choice);
                cout << GREEN << "[Success] " << RESET << " After Sorting:" << endl;
                Display('F');
            }
        }
        else if (choice == 2)
        {
            if (Ve.Variable_Expenditure_Amount.empty() || Ve.Variable_Expenditure_Date.empty() || Ve.Variable_Expenditure_Name.empty())
            {
                cout << RED << "[Error] " << RESET << " No Variable Expenses to sort." << endl;
                cout << YELLOW << "[Prompt] " << RESET << " Please Enter Some expenses to sort." << endl;
            }
            else
            {
                cout << YELLOW << "[Prompt] " << RESET << " By which Metric do you want to sort Variable Expenses?" << endl;
                cout << "A by Name" << endl;
                cout << "B by Amount" << endl;
                cout << "C by Date" << endl;

                bool isValid = false;
                while (!isValid)
                {
                    cin >> Choice;
                    if (Choice == 'A' || Choice == 'B' || Choice == 'C')
                    {
                        isValid = true;
                    }
                    else
                    {
                        cout << RED << "[Error] " << RESET << " Invalid Choice. Please Enter A, B, or C." << endl;
                    }
                }

                SortVec(Ve.Variable_Expenditure_Name, Ve.Variable_Expenditure_Date, Ve.Variable_Expenditure_Amount, Choice);
                cout << GREEN << "[Success] " << RESET << " After Sorting:" << endl;
                Display('V');
            }
        }
    }

    void Display(char ch)
    {
        if (ch == 'F')
        { // Display Fixed Expenditures
            if (Fe.Fixed_Expenditure_Amount.empty())
            {
                cout << RED << "[Error] " << RESET << " No Fixed Expenditures to display." << endl;
                return;
            }
            cout << "+" << string(65, '-') << "+" << endl;
            cout << "| " << left << setw(28) << "Fixed Expense Name"
                 << "| " << setw(13) << "Date"
                 << "| " << right << setw(15) << "Amount " << "|" << endl;
            cout << "+" << string(65, '-') << "+" << endl;

            for (int i = 0; i < Fe.Fixed_Expenditure_Name.size(); ++i)
            {
                cout << "| " << left << setw(28) << Fe.Fixed_Expenditure_Name[i]
                     << "| " << setw(13) << Fe.Fixed_Expenditure_Date[i]
                     << "| " << right << setw(14) << fixed << setprecision(2) << Fe.Fixed_Expenditure_Amount[i] << " |" << endl;
            }
            cout << "+" << string(65, '-') << "+" << endl;
        }
        else if (ch == 'V')
        { // Display Variable Expenditures
            if (Ve.Variable_Expenditure_Amount.empty())
            {
                cout << RED << "[Error] " << RESET << " No Variable Expenditures to display." << endl;
                return;
            }
            cout << "+" << string(65, '-') << "+" << endl;
            cout << "| " << left << setw(28) << "Variable Expense Name"
                 << "| " << setw(13) << "Date"
                 << "| " << right << setw(15) << "Amount " << "|" << endl;
            cout << "+" << string(65, '-') << "+" << endl;

            for (int i = 0; i < Ve.Variable_Expenditure_Name.size(); ++i)
            {
                cout << "| " << left << setw(28) << Ve.Variable_Expenditure_Name[i]
                     << "| " << setw(13) << Ve.Variable_Expenditure_Date[i]
                     << "| " << right << setw(14) << fixed << setprecision(2) << Ve.Variable_Expenditure_Amount[i] << " |" << endl;
            }
            cout << "+" << string(65, '-') << "+" << endl;
        }
    }

    void GenerateExpenditureReport() const
    {
        ofstream reportFile("ExpenditureReport.txt");

        if (!reportFile.is_open())
        {
            cerr << RED << "[Error] " << RESET << " Could not open file for writing." << endl;
            return;
        }

        reportFile << "============================ Expenditure Report ============================\n";
        reportFile << "\nFixed Expenditures:\n";
        reportFile << left << setw(30) << "Expense Name" << setw(15) << "Date" << right << setw(10) << "Amount" << endl;
        reportFile << string(55, '-') << endl;

        for (int i = 0; i < Fe.Fixed_Expenditure_Name.size(); ++i)
        {
            reportFile << left << setw(30) << Fe.Fixed_Expenditure_Name[i]
                       << setw(15) << Fe.Fixed_Expenditure_Date[i]
                       << right << setw(10) << fixed << setprecision(2) << Fe.Fixed_Expenditure_Amount[i] << endl;
        }

        reportFile << "\nVariable Expenditures:\n";
        reportFile << left << setw(30) << "Expense Name" << setw(15) << "Date" << right << setw(10) << "Amount" << endl;
        reportFile << string(55, '-') << endl;

        for (int i = 0; i < Ve.Variable_Expenditure_Name.size(); ++i)
        {
            reportFile << left << setw(30) << Ve.Variable_Expenditure_Name[i]
                       << setw(15) << Ve.Variable_Expenditure_Date[i]
                       << right << setw(10) << fixed << setprecision(2) << Ve.Variable_Expenditure_Amount[i] << endl;
        }

        reportFile << "\nSummary:\n";
        reportFile << string(55, '-') << endl;
        reportFile << left << setw(45) << "Total Expenditure:" << right << setw(10) << fixed << setprecision(2) << total_expenditure << endl;
        reportFile << string(55, '-') << endl;

        reportFile.close();
        cout << GREEN << "[Success] " << RESET << " Expenditure report has been generated and saved as 'ExpenditureReport.txt'." << endl;
    }

    void Reset()
    {
        total_expenditure = 0;
        Fe.Reset();
        Ve.Reset();
    }

    void Commit(FixedExpenditure &f, VariableExpenditure &v)
    {
        if (Fe.Fixed_Expenditure_Amount.empty() && Ve.Variable_Expenditure_Amount.empty())
        {
            cout << RED << "[Error] " << RESET << " There are no Expenditures to commit." << endl;
            return;
        }

        if (!Fe.Fixed_Expenditure_Amount.empty())
        {
            f = Fe;
            cout << GREEN << "[Success] " << RESET << " Fixed Expenditure Data Committed." << endl;
        }
        else
        {
            cout << YELLOW << "[Prompt] " << RESET << " No Fixed Expenditure Data available to commit." << endl;
        }

        if (!Ve.Variable_Expenditure_Amount.empty())
        {
            v = Ve;
            cout << GREEN << "[Success] " << RESET << " Variable Expenditure Data Committed." << endl;
        }
        else
        {
            cout << YELLOW << "[Prompt] " << RESET << " No Variable Expenditure Data available to commit." << endl;
        }
    }
    friend class FinanceHub;
    friend class User;
};

class Budget
{
    vector<string> Category;
    vector<double> Amount;
    FixedExpenditure Fe;
    VariableExpenditure Ve;

public:
    void Copy(const FixedExpenditure fe, const VariableExpenditure ve)
    {
        if (fe.Fixed_Expenditure_Amount.empty())
            cerr << RED << "[Error] " << RESET << " Please Enter Some Fixed Expenses.";
        else if (ve.Variable_Expenditure_Amount.empty())
            cerr << RED << "[Error] " << RESET << " Please Enter Some Variable Expenses.";
        else
        {
            Fe = fe;
            Ve = ve;
        }
    }

    void RecordBudget()
    {
        string Category_name;
        double Category_amount;
        Choice = 'Y';
        while (Choice == 'Y' || Choice == 'y')
        {
            cout << YELLOW << "[Prompt] " << RESET << "Please enter A, B or C (Operating Budget, Capital Budget, or Cash Flow Budget respectively):" << RESET << endl;
            cin.ignore();
            cin >> Choice;
            switch (Choice)
            {
            case 'A':
                Category_name = "Operating Budget";
                break;
            case 'B':
                Category_name = "Capital Budget";
                break;
            case 'C':
                Category_name = "Cash Flow Budget";
                break;
            default:
                cout << RED << "[Error] " << RESET << " Invalid choice. Please enter A, B, or C." << endl;
                continue;
            }

            bool isPresent = false;
            for (const auto &category : Category)
            {
                if (category == Category_name)
                {
                    isPresent = true;
                    break;
                }
            }

            if (isPresent)
            {
                cout << YELLOW << "[Warning]" << RESET << " The category '" << Category_name << "' already exists. Please choose a different category or update the existing one." << endl;
            }
            else
            {
                cout << YELLOW << "[Prompt] " << RESET << "Please enter the amount of " << Category_name << ":" << RESET << endl;
                cin >> Category_amount;
                Category.push_back(Category_name);
                Amount.push_back(Category_amount);
                cout << YELLOW << " [Prompt] " << RESET << "Do you want to add another budget? (Y for Yes or N for No): " << RESET;
                cin >> Choice;
            }
        }
    }

    void OperationsonBudget()
    {
        choice = 0;
        cout << YELLOW << "[Prompt] " << RESET << "Enter 1 to Display Budgets.\nEnter 2 to Update Budget.\nEnter 3 to Remove Budget.\nEnter 4 to Get Total Budget.\nEnter 5 to Search and Sort Specific Budgets.\nEnter 6 to Compare Budget Versus Actual Expenses.\n";
        cin >> choice;

        string categoryToUpdate;
        string categoryToRemove;
        double newAmount;
        bool found;
        auto it = Category.end();
        char SortType;
        vector<int> indices;
        int order;
        double Fixed_Expense_Amount = 0.0, Variable_Expense_Amount = 0.0, Budget_Amount = 0.0;
        string Fixed_Budget_Status;
        string Variable_Budget_Status;
        char reportChoice = 'N';
        string categoryToUpdateName;
        string categoryToRemoveName;
        switch (choice)
        {
        case 1:
            cout << left << setw(25) << "Category" << right << setw(15) << "Amount" << endl;
            cout << string(40, '-') << endl;

            for (int i = 0; i < Category.size(); ++i)
            {
                cout << left << setw(25) << Category[i]
                     << right << setw(15) << fixed << setprecision(2) << Amount[i] << endl;
            }
            break;

        case 2:
            cout << YELLOW << "[Prompt] " << RESET << "Enter A for Operating Budget, B for Capital Budget, or C for Cash Flow Budget: ";
            char updateChoice;
            cin >> updateChoice;

            switch (updateChoice)
            {
            case 'A':
                categoryToUpdateName = "Operating Budget";
                break;
            case 'B':
                categoryToUpdateName = "Capital Budget";
                break;
            case 'C':
                categoryToUpdateName = "Cash Flow Budget";
                break;
            default:
                cout << RED << "[Error] " << RESET << "Invalid choice." << endl;
                break;
            }

            found = false;
            for (int i = 0; i < Category.size(); ++i)
            {
                if (Category[i] == categoryToUpdateName)
                {
                    cout << GREEN << "[Success] " << RESET << "Enter the new amount for " << categoryToUpdateName << ": ";
                    cin >> newAmount;
                    Amount[i] = newAmount;
                    found = true;
                    cout << GREEN << "[Success] " << RESET << "Budget for " << categoryToUpdateName << " updated successfully!" << endl;
                    break;
                }
            }

            if (!found)
            {
                cout << RED << "[Error] " << RESET << "Category '" << categoryToUpdateName << "' not found." << endl;
            }
            break;

        case 3:
            cout << YELLOW << "[Prompt] " << RESET << "Enter A for Operating Budget, B for Capital Budget, or C for Cash Flow Budget: ";
            char removeChoice;
            cin >> removeChoice;

            switch (removeChoice)
            {
            case 'A':
                categoryToRemoveName = "Operating Budget";
                break;
            case 'B':
                categoryToRemoveName = "Capital Budget";
                break;
            case 'C':
                categoryToRemoveName = "Cash Flow Budget";
                break;
            default:
                cout << RED << "[Error] " << RESET << "Invalid choice." << endl;
                break;
            }

            it = find(Category.begin(), Category.end(), categoryToRemoveName);
            if (it != Category.end())
            {
                int index = distance(Category.begin(), it);
                Category.erase(it);
                Amount.erase(Amount.begin() + index);
                cout << GREEN << "[Success] " << RESET << "Budget for '"
                     << categoryToRemoveName << "' removed successfully!" << endl;
            }
            else
            {
                cout << RED << "[Error] " << RESET << categoryToRemoveName << "' not found." << endl;
            }
            break;

        case 4:
            Budget_Amount = 0;
            for (const auto &amount : Amount)
            {
                Budget_Amount += amount;
            }
            cout << "Total Budget: " << fixed << setprecision(2) << Budget_Amount << endl;
            break;

        case 5:
            cout << YELLOW << "[Prompt] " << RESET << "Enter 'C' to Sort by Categories or 'A' to sort by Amounts: ";
            cin >> SortType;

            indices.resize(Category.size());
            for (int i = 0; i < Category.size(); ++i)
            {
                indices[i] = i;
            }

            if (SortType == 'C' || SortType == 'c')
            {
                cout << YELLOW << "[Prompt] " << RESET << "Enter 1 to sort Budgets in Ascending Order of Categories" << endl;
                cout << YELLOW << "[Prompt] " << RESET << "Enter 2 to sort Budgets in Descending Order of Categories" << endl;
                while (true)
                {
                    cin >> order;
                    if (order == 1 || order == 2)
                    {
                        bool ascending = (order == 1);
                        sort(indices.begin(), indices.end(), [ascending, this](int i1, int i2)
                             { return ascending ? Category[i1] < Category[i2] : Category[i1] > Category[i2]; });
                        break;
                    }
                    else
                    {
                        cout << RED << "[Error] " << RESET << "Invalid Number. Enter 1 or 2 only" << endl;
                    }
                }

                cout << left << setw(25) << "Category" << right << setw(15) << "Amount" << endl;
                cout << string(40, '-') << endl;
                for (int index : indices)
                {
                    cout << left << setw(25) << Category[index]
                         << right << setw(15) << fixed << setprecision(2) << Amount[index] << endl;
                }
            }
            else if (SortType == 'A' || SortType == 'a')
            {
                cout << YELLOW << "[Prompt] " << RESET << "Enter 1 to sort Budgets in Ascending Order of Amounts" << endl;
                cout << YELLOW << "[Prompt] " << RESET << "Enter 2 to sort Budgets in Descending Order of Amounts" << endl;
                while (true)
                {
                    cin >> order;
                    if (order == 1 || order == 2)
                    {
                        bool ascending = (order == 1);
                        sort(indices.begin(), indices.end(), [ascending, this](int i1, int i2)
                             { return ascending ? Amount[i1] < Amount[i2] : Amount[i1] > Amount[i2]; });
                        break;
                    }
                    else
                    {
                        cout << RED << "[Error] " << RESET << "Invalid Number. Enter 1 or 2 only" << endl;
                    }
                }

                cout << left << setw(25) << "Category" << right << setw(15) << "Amount" << endl;
                cout << string(40, '-') << endl;
                for (int index : indices)
                {
                    cout << left << setw(25) << Category[index]
                         << right << setw(15) << fixed << setprecision(2) << Amount[index] << endl;
                }
            }
            else
            {
                cout << RED << "[Error] " << RESET << "Invalid Input. Enter A or C only!" << endl;
            }
            break;

        case 6:
            cout << GREEN << "[Success] " << RESET << endl;
            cout << "\n--- Budget vs Actual Expenses Comparison ---\n";

            Fixed_Expense_Amount = 0.0;
            Variable_Expense_Amount = 0.0;
            Budget_Amount = 0.0;
            for (int i = 0; i < Fe.Fixed_Expenditure_Amount.size(); ++i)
                Fixed_Expense_Amount += Fe.Fixed_Expenditure_Amount[i];
            for (int i = 0; i < Ve.Variable_Expenditure_Amount.size(); ++i)
                Variable_Expense_Amount += Ve.Variable_Expenditure_Amount[i];
            for (int i = 0; i < Amount.size(); ++i)
                Budget_Amount += Amount[i];

            cout << left << setw(30) << "Total Fixed Expenses"
                 << right << setw(15) << fixed << setprecision(2) << Fixed_Expense_Amount << endl;
            cout << left << setw(30) << "Total Variable Expenses"
                 << right << setw(15) << fixed << setprecision(2) << Variable_Expense_Amount << endl;
            cout << left << setw(30) << "Total Budget Amount"
                 << right << setw(15) << fixed << setprecision(2) << Budget_Amount << endl;

            Fixed_Budget_Status = Budget_Amount > Fixed_Expense_Amount ? "Under Budget" : "Over Budget";
            Variable_Budget_Status = Budget_Amount > Variable_Expense_Amount ? "Under Budget" : "Over Budget";
            cout << left << setw(30) << "Fixed Expense Status: " << Fixed_Budget_Status << endl;
            cout << left << setw(30) << "Variable Expense Status: " << Variable_Budget_Status << endl;

            cout << YELLOW << "[Prompt] " << RESET << "Do you want to generate a Report of Your Budgeting? (Y for Yes, N for No): ";
            cin >> reportChoice;
            if (reportChoice == 'Y' || reportChoice == 'y')
            {
                ofstream reportFile("BudgetReport.txt");

                if (!reportFile.is_open())
                {
                    cerr << RED << "[Error] " << RESET << "Error: Could not open file for writing." << endl;
                    break;
                }

                reportFile << "============================ Budget Report ============================\n";
                reportFile << "\nBudget Categories:\n";
                reportFile << left << setw(25) << "Category" << right << setw(15) << "Amount" << endl;
                reportFile << string(40, '-') << endl;

                for (int i = 0; i < Category.size(); ++i)
                {
                    reportFile << left << setw(25) << Category[i]
                               << right << setw(15) << fixed << setprecision(2) << Amount[i] << endl;
                }

                reportFile << "\nSummary:\n";
                reportFile << string(40, '-') << endl;
                reportFile << left << setw(30) << "Total Budget:" << right << setw(10) << fixed << setprecision(2) << Budget_Amount << endl;
                reportFile << left << setw(30) << "Total Fixed Expenses:" << right << setw(10) << fixed << setprecision(2) << Fixed_Expense_Amount << endl;
                reportFile << left << setw(30) << "Total Variable Expenses:" << right << setw(10) << fixed << setprecision(2) << Variable_Expense_Amount << endl;

                reportFile << string(40, '-') << endl;
                reportFile << left << setw(30) << "Fixed Expense Status:" << Fixed_Budget_Status << endl;
                reportFile << left << setw(30) << "Variable Expense Status:" << Variable_Budget_Status << endl;

                reportFile.close();
                cout << GREEN << "[Success] " << RESET << "Budget report generated successfully!"
                     << endl;
            }
            break;

        default:
            cout << RED << "[Error] " << RESET << "Invalid option! Please select a valid choice." << endl;
            break;
        }
    }

    void ResetBudget()
    {
        Category.clear();
        Amount.clear();
        cout << GREEN << "[Sucess]" << RESET << " Budget reseted succesfully." << endl;
    }

    friend class FinanceHub;
    friend class User;
};

double Growth(string Currdate, string AcqDate, double AcqCost, double CurCost)
{
    // CAGR (Compund Annual Growth Rate) Formula = ((Ending Value / Beggining Value)^ 1/n) - 1
    double Years_Of_Investment;
    Years_Of_Investment = stoi(Currdate.substr(0, 4)) - stoi(AcqDate.substr(0, 4));
    double growthRate = pow((CurCost / AcqCost), (1.0 / Years_Of_Investment)) - 1;
    return growthRate * 100;
}

class Asset
{
private:
    string Asset_Name;
    int Asset_Quantity;
    double Asset_Acquisition_Cost;
    string Asset_Acquisition_Date;
    double Asset_Liquidity;
    double Asset_Current_Value;
    string Asset_Current_Date;
    double Asset_Growth_Rate;

public:
    void setValues(const string &name, int quantity, double acqCost, const string &acqDate,
                   double liquidity, double curValue, const string &curDate, double growthRate)
    {
        Asset_Name = name;
        Asset_Quantity = quantity;
        Asset_Acquisition_Cost = acqCost;
        Asset_Acquisition_Date = acqDate;
        Asset_Liquidity = liquidity;
        Asset_Current_Value = curValue;
        Asset_Current_Date = curDate;
        Asset_Growth_Rate = growthRate;
    }

    string getName() const { return Asset_Name; }
    int getQuantity() const { return Asset_Quantity; }
    double getAcquisitionCost() const { return Asset_Acquisition_Cost; }
    string getAcquisitionDate() const { return Asset_Acquisition_Date; }
    double getLiquidity() const { return Asset_Liquidity; }
    double getCurrentValue() const { return Asset_Current_Value; }
    string getCurrentDate() const { return Asset_Current_Date; }
    double getGrowthRate() const { return Asset_Growth_Rate; }

    friend class FinanceHub;
    friend class User;
};

void RecordAssets(vector<Asset> &Asset_List)
{
    char Choice = 'Y';
    while (Choice == 'Y' || Choice == 'y')
    {
        string Name;
        int Quantity;
        double Aquisition_Cost, Current_Cost, Liquidity, Growth_Rate;
        string Acq_Date, Cur_Date;

        cout << YELLOW << "[Prompt] " << RESET << " Enter Asset Name: ";
        cin.ignore();
        getline(cin, Name);
        cout << YELLOW << "[Prompt] " << RESET << " How much Quantity of " << Name << " do you own: ";
        cin >> Quantity;
        cout << YELLOW << "[Prompt] " << RESET << " How much was the Acquisition cost of " << Name << " X " << Quantity << ": ";
        cin >> Aquisition_Cost;
        cout << YELLOW << "[Prompt] " << RESET << " How much is your Asset worth now: ";
        cin >> Current_Cost;
        cout << YELLOW << "[Prompt] " << RESET << " What Would Be the Liquidity Percentage of your Asset: ";
        cin >> Liquidity;
        cout << YELLOW << "[Prompt] " << RESET << " Please Enter The Date you Acquired this Asset: \n";
        Acq_Date = validate('D');
        cout << YELLOW << "[Prompt] " << RESET << " Please Enter Current Time: \n";
        Cur_Date = validate('D');

        Growth_Rate = Growth(Cur_Date, Acq_Date, Aquisition_Cost, Current_Cost);
        Asset New_Asset;
        New_Asset.setValues(Name, Quantity, Aquisition_Cost, Acq_Date, Liquidity, Current_Cost, Cur_Date, Growth_Rate);
        Asset_List.push_back(New_Asset);

        cout << GREEN << "[Success] " << RESET << " Asset added successfully." << endl;
        cout << YELLOW << "[Prompt] " << RESET << " Do you Want to Add another Investment? (Y for Yes, N for No): ";
        cin >> Choice;
        while (Choice != 'Y' && Choice != 'y' && Choice != 'N' && Choice != 'n')
        {
            cout << RED << "[Error] " << RESET << " Invalid input. Please enter Y or N." << endl;
            cout << YELLOW << "[Prompt] " << RESET << " Do you Want to Add another Investment? (Y for Yes, N for No): ";
            cin >> Choice;
        }
    }
}

void DisplayAssets(const vector<Asset> &Asset_List)
{
    if (Asset_List.empty())
    {
        cout << RED << "[Error] " << RESET << " No Assets Recorded Yet." << endl;
        return;
    }

    cout << GREEN << "[Info]" << RESET << " Asset List:" << endl;
    cout << "+" << string(95, '-') << "+" << endl;
    cout << "|" << left << setw(20) << " Investment Name"
         << "|" << setw(15) << " Acq. Date"
         << "|" << right << setw(15) << "Acq. Cost "
         << "|" << right << setw(15) << "Curr. Value "
         << "|" << right << setw(15) << "Growth Rate% "
         << "|" << endl;
    cout << "+" << string(95, '-') << "+" << endl;

    for (const Asset &asset : Asset_List)
    {
        cout << "|" << left << " " << setw(19) << asset.getName()
             << "|" << " " << setw(14) << asset.getAcquisitionDate()
             << "|" << right << setw(14) << fixed << setprecision(2) << asset.getAcquisitionCost() << " "
             << "|" << right << setw(14) << asset.getCurrentValue() << " "
             << "|" << right << setw(14) << asset.getGrowthRate() << " "
             << "|" << endl;
    }
    cout << "+" << string(95, '-') << "+" << endl;
    cout << GREEN << "[Success] " << RESET << " Assets displayed successfully." << endl;
}

void ModifyAsset(vector<Asset> &Asset_List, int index)
{
    if (Asset_List.empty())
    {
        cout << RED << "[Error] " << RESET << " No Assets Recorded." << endl;
        return;
    }
    if (index < 0 || index >= Asset_List.size())
    {
        cout << RED << "[Error] " << RESET << " Invalid index! Unable to modify asset." << endl;
        return;
    }

    Asset &asset = Asset_List[index];
    cout << GREEN << "[Info]" << RESET << " Modifying Asset: " << asset.getName() << endl;

    string newName;
    int newQuantity;
    double newAcquisitionCost, newCurrentValue, newLiquidity;
    string newAcquisitionDate, newCurrentDate;

    cout << YELLOW << "[Prompt] " << RESET << " Enter new Investment Name (current: " << asset.getName() << "): ";
    cin.ignore();
    getline(cin, newName);
    cout << YELLOW << "[Prompt] " << RESET << " Enter new Quantity (current: " << asset.getQuantity() << "): ";
    cin >> newQuantity;
    cout << YELLOW << "[Prompt] " << RESET << " Enter new Acquisition Cost (current: " << asset.getAcquisitionCost() << "): ";
    cin >> newAcquisitionCost;
    cout << YELLOW << "[Prompt] " << RESET << " Enter new Current Value (current: " << asset.getCurrentValue() << "): ";
    cin >> newCurrentValue;
    cout << YELLOW << "[Prompt] " << RESET << " Enter new Liquidity Percentage (current: " << asset.getLiquidity() << "): ";
    cin >> newLiquidity;
    cout << YELLOW << "[Prompt] " << RESET << " Enter new Acquisition Date (current: " << asset.getAcquisitionDate() << "): \n";
    newAcquisitionDate = validate('D');
    cout << YELLOW << "[Prompt] " << RESET << " Enter new Current Date (current: " << asset.getCurrentDate() << "): \n";
    newCurrentDate = validate('D');

    double newGrowthRate = Growth(newCurrentDate, newAcquisitionDate, newAcquisitionCost, newCurrentValue);
    asset.setValues(newName, newQuantity, newAcquisitionCost, newAcquisitionDate, newLiquidity,
                    newCurrentValue, newCurrentDate, newGrowthRate);

    cout << GREEN << "[Success] " << RESET << " Asset updated successfully!" << endl;
}

void Portfolio(vector<Asset> &Asset_List)
{
    float Total_Value = 0.0, Total_Profit = 0.0, Total_Loss = 0.0, Total_Liquid_Value = 0.0;
    float Average_Growth_Rate = 0.0, Total_Initial_Investment = 0.0;
    int Total_Assets = Asset_List.size();

    // Calculate various portfolio metrics
    for (int i = 0; i < Asset_List.size(); ++i)
    {
        // Calculate total current value of portfolio
        Total_Value += Asset_List[i].getCurrentValue();

        // Calculate total initial investment
        Total_Initial_Investment += Asset_List[i].getAcquisitionCost();

        // Calculate profits and losses
        float profit_loss = Asset_List[i].getCurrentValue() - Asset_List[i].getAcquisitionCost();
        if (profit_loss > 0)
            Total_Profit += profit_loss;
        else
            Total_Loss += abs(profit_loss);

        // Calculate total liquid value
        Total_Liquid_Value += Asset_List[i].getCurrentValue() * Asset_List[i].getLiquidity();

        // Sum up growth rates for average calculation
        Average_Growth_Rate += Asset_List[i].getGrowthRate();
    }

    // Calculate average growth rate
    Average_Growth_Rate = (Total_Assets > 0) ? Average_Growth_Rate / Total_Assets : 0;
    cout << GREEN << "[Portfolio]" << RESET << endl;
    // Display Portfolio Summary
    cout << "\n========== Portfolio Summary ==========" << endl;
    cout << fixed << setprecision(2);

    // Basic Portfolio Statistics
    cout << "\n1. Basic Statistics:" << endl;
    cout << "   Total Number of Assets: " << Total_Assets << endl;
    cout << "   Total Portfolio Value: $" << Total_Value << endl;
    cout << "   Total Initial Investment: $" << Total_Initial_Investment << endl;

    // Profit/Loss Analysis
    cout << "\n2. Profit/Loss Analysis:" << endl;
    cout << "   Total Profits: $" << Total_Profit << endl;
    cout << "   Total Losses: $" << Total_Loss << endl;
    cout << "   Net Profit/Loss: $" << (Total_Profit - Total_Loss) << endl;
    float roi = ((Total_Value - Total_Initial_Investment) / Total_Initial_Investment) * 100;
    cout << "   Overall ROI: " << roi << "%" << endl;

    // Portfolio Performance
    cout << "\n3. Performance Metrics:" << endl;
    cout << "   Average Growth Rate: " << Average_Growth_Rate << "%" << endl;
    cout << "   Total Liquid Value: $" << Total_Liquid_Value << endl;
    cout << "   Portfolio Liquidity Ratio: " << (Total_Liquid_Value / Total_Value * 100) << "%" << endl;

    // Asset Distribution Analysis
    cout << "\n4. Asset Distribution:" << endl;
    for (int i = 0; i < Asset_List.size(); ++i)
    {
        float percentage = (Asset_List[i].getCurrentValue() / Total_Value) * 100;
        cout << "   " << Asset_List[i].getName() << ": "
             << percentage << "% of portfolio" << endl;
    }

    // Best and Worst Performing Assets
    if (Total_Assets > 0)
    {
        int best_performer_idx = 0;
        int worst_performer_idx = 0;
        float best_growth = Asset_List[0].getGrowthRate();
        float worst_growth = Asset_List[0].getGrowthRate();

        for (int i = 1; i < Asset_List.size(); ++i)
        {
            if (Asset_List[i].getGrowthRate() > best_growth)
            {
                best_growth = Asset_List[i].getGrowthRate();
                best_performer_idx = i;
            }
            if (Asset_List[i].getGrowthRate() < worst_growth)
            {
                worst_growth = Asset_List[i].getGrowthRate();
                worst_performer_idx = i;
            }
        }

        cout << "\n5. Performance Extremes:" << endl;
        cout << "   Best Performing Asset: " << Asset_List[best_performer_idx].getName()
             << " (" << best_growth << "% growth)" << endl;
        cout << "   Worst Performing Asset: " << Asset_List[worst_performer_idx].getName()
             << " (" << worst_growth << "% growth)" << endl;
    }

    // Risk Analysis based on liquidity
    cout << "\n6. Risk Analysis:" << endl;
    float high_liquidity_value = 0.0;
    float medium_liquidity_value = 0.0;
    float low_liquidity_value = 0.0;

    for (int i = 0; i < Asset_List.size(); ++i)
    {
        float liquidity = Asset_List[i].getLiquidity();
        float value = Asset_List[i].getCurrentValue();

        if (liquidity >= 0.7)
            high_liquidity_value += value;
        else if (liquidity >= 0.3)
            medium_liquidity_value += value;
        else
            low_liquidity_value += value;
    }

    cout << "   High Liquidity Assets (>70%): $" << high_liquidity_value
         << " (" << (high_liquidity_value / Total_Value * 100) << "%)" << endl;
    cout << "   Medium Liquidity Assets (30-70%): $" << medium_liquidity_value
         << " (" << (medium_liquidity_value / Total_Value * 100) << "%)" << endl;
    cout << "   Low Liquidity Assets (<30%): $" << low_liquidity_value
         << " (" << (low_liquidity_value / Total_Value * 100) << "%)" << endl;

    cout << "\n======================================" << endl;
    cout << GREEN << "[Success] " << RESET << "Portfolio Dosplayed Successfully." << endl;
}

void Filter(const vector<Asset> &Asset_List)
{
    while (true)
    {
        cout << YELLOW << "[Prompt]  " << RESET << "Enter Which Metric Do you Want to filter the Data: " << endl;
        cout << "1. Search by name" << endl;
        cout << "2. Filter by growth rate range" << endl;
        cout << "3. Filter by value range" << endl;
        cout << "4. Filter by acquisition date" << endl;
        cout << "5. Filter by liquidity threshold" << endl;
        cout << "6. Return to main menu" << endl;
        cout << YELLOW << "[Prompt]  " << RESET << "Enter Your Choice (1-6): ";

        int choice;
        cin >> choice;
        if (choice == 6)
            break;

        bool Found = false;

        switch (choice)
        {
        case 1: // Search by name
        {
            string name;
            cout << YELLOW << "[Prompt]  " << RESET << "Enter the name of the asset you want to search for: ";
            cin.ignore();
            getline(cin, name);

            cout << "\nMatching Assets:" << endl;
            cout << left << setw(15) << "Name"
                 << right << setw(12) << "Value"
                 << setw(15) << "Growth Rate" << endl;
            cout << string(42, '-') << endl;

            for (const auto &asset : Asset_List)
            {
                if (name == asset.getName())
                {
                    Found = true;
                    cout << left << setw(15) << asset.getName()
                         << right << setw(12) << asset.getCurrentValue()
                         << setw(15) << asset.getGrowthRate() << "%" << endl;
                }
            }

            if (!Found)
                cout << RED << "[Error]  " << RESET << "No assets found with the name: " << name << endl;

            break;
        }
        case 2: // Filter by growth rate range
        {
            double minGrowth, maxGrowth;
            cout << YELLOW << "[Prompt]  " << RESET << "Enter Minimum Growth Rate: ";
            cin >> minGrowth;
            cout << YELLOW << "[Prompt]  " << RESET << "Enter Maximum Growth Rate: ";
            cin >> maxGrowth;

            cout << "\nAssets with growth rate between " << minGrowth << "% and " << maxGrowth << "%:" << endl;
            cout << left << setw(15) << "Name"
                 << right << setw(12) << "Value"
                 << setw(15) << "Growth Rate" << endl;
            cout << string(42, '-') << endl;

            for (const auto &asset : Asset_List)
            {
                if (asset.getGrowthRate() >= minGrowth && asset.getGrowthRate() <= maxGrowth)
                {
                    Found = true;
                    cout << left << setw(15) << asset.getName()
                         << right << setw(12) << asset.getCurrentValue()
                         << setw(15) << asset.getGrowthRate() << "%" << endl;
                }
            }

            if (!Found)
                cout << RED << "[Error]  " << RESET << "No assets found within this growth rate range." << endl;

            break;
        }
        case 3: // Filter by value range
        {
            double minValue, maxValue;
            cout << YELLOW << "[Prompt]  " << RESET << "Enter Minimum Value: ";
            cin >> minValue;
            cout << YELLOW << "[Prompt]  " << RESET << "Enter Maximum Value: ";
            cin >> maxValue;

            cout << "\nAssets with value between " << minValue << " and " << maxValue << ":" << endl;
            cout << left << setw(15) << "Name"
                 << right << setw(12) << "Value"
                 << setw(15) << "Growth Rate" << endl;
            cout << string(42, '-') << endl;

            for (const auto &asset : Asset_List)
            {
                if (asset.getCurrentValue() >= minValue && asset.getCurrentValue() <= maxValue)
                {
                    Found = true;
                    cout << left << setw(15) << asset.getName()
                         << right << setw(12) << asset.getCurrentValue()
                         << setw(15) << asset.getGrowthRate() << "%" << endl;
                }
            }

            if (!Found)
                cout << RED << "[Error]  " << RESET << "No assets found within this value range." << endl;

            break;
        }
        case 4: // Filter by acquisition date
        {
            string startDate, endDate;
            cout << YELLOW << "[Prompt]  " << RESET << "Enter Start Date (YYYY-MM-DD): \n";
            startDate = validate('D');
            cout << YELLOW << "[Prompt]  " << RESET << "Enter End Date (YYYY-MM-DD): \n";
            endDate = validate('D');

            cout << "\nAssets acquired between " << startDate << " and " << endDate << ":" << endl;
            cout << left << setw(15) << "Name"
                 << setw(12) << "Acq. Date"
                 << right << setw(15) << "Value" << endl;
            cout << string(42, '-') << endl;

            for (const auto &asset : Asset_List)
            {
                string acqDate = asset.getAcquisitionDate();
                if (acqDate >= startDate && acqDate <= endDate)
                {
                    Found = true;
                    cout << left << setw(15) << asset.getName()
                         << setw(12) << acqDate
                         << right << setw(15) << asset.getCurrentValue() << endl;
                }
            }

            if (!Found)
                cout << RED << "[Error]  " << RESET << "No assets found within this acquisition date range." << endl;

            break;
        }
        case 5: // Filter by liquidity threshold
        {
            double minLiquidity;
            cout << YELLOW << "[Prompt]  " << RESET << "Enter the minimum liquidity threshold: ";
            cin >> minLiquidity;

            cout << "\nAssets with liquidity greater than " << minLiquidity << ":" << endl;
            cout << left << setw(15) << "Name"
                 << right << setw(12) << "Value"
                 << setw(15) << "Liquidity" << endl;
            cout << string(42, '-') << endl;

            for (const auto &asset : Asset_List)
            {
                if (asset.getLiquidity() >= minLiquidity) // Assuming Asset class has getLiquidity() method
                {
                    Found = true;
                    cout << left << setw(15) << asset.getName()
                         << right << setw(12) << asset.getCurrentValue()
                         << setw(15) << asset.getLiquidity() << endl;
                }
            }

            if (!Found)
                cout << RED << "[Error]  " << RESET << "No assets found with liquidity above this threshold." << endl;

            break;
        }
        default:
            cout << RED << "[Error]  " << RESET << "Invalid choice, please try again." << endl;
            break;
        }
    }
}

void Reset(vector<Asset> &Asset_List)
{
    if (Asset_List.empty())
    {
        cout << RED << "[Error] " << "Please Enter Some Assets First" << endl;
        return;
    }
    Asset_List.clear();
    cout << GREEN << "[Success] " << RESET << " All assets have been deleted." << endl;
}

class Assets
{
    vector<Asset> Asset_List;

public:
    void RecordAssetes()
    {
        RecordAssets(Asset_List);
    }
    void DisplayAsstes()
    {
        DisplayAssets(Asset_List);
    }

    void ModifyAsstes()
    {
        if (Asset_List.empty())
        {
            cout << RED << "[Error]  " << RESET << "No assets to modify." << endl;
            return;
        }
        int index;
        cout << YELLOW << "[Prompt]  " << RESET << "Enter the index of the asset you want to modify (0 to " << Asset_List.size() - 1 << "): ";

        cin >> index;
        if (index >= 0 && index < Asset_List.size())
        {
            ModifyAsset(Asset_List, index);
            cout << GREEN << "[Success]  " << RESET << "Asset modified successfully." << endl; // Assuming successful modification
        }
        else
        {
            cout << RED << "[Error]  " << RESET << "Wrong Index Entered!" << endl;
        }
    }

    void ShowPortfolio()
    {
        Portfolio(Asset_List);
    }
    void FilterAsstess()
    {
        Filter(Asset_List);
    }

    void ResetAssets()
    {
        Reset(Asset_List);
    }
    friend class FinanceHub;
    friend class User;
};

class User
{
    // User Credentials
    string username, password, Email, DOB, RegistrationDate;
    bool isLoggedin;

    static bool isDatabaseCreated;
    static bool isUserdataDatabaseCreated;

public:
    // Register a new user
    void Register()
    {
        username = validate('U');

        password = validate('P');

        Email = validate('E');

        cout << YELLOW << "[Prompt] " << RESET << " Enter Your Date-Of-Birth (DOB)" << endl;
        DOB = validate('D');

        cout << YELLOW << "[Prompt] " << RESET << " Enter Your Registration Date" << endl;
        RegistrationDate = validate('D');

        // Check if the user is already registered
        if (isUserRegistered(username, Email))
        {
            cout << RED << "[Error] " << RESET << " User with this username or email already exists!" << endl;
            return;
        }

        // Save user data to the database
        SimulateDatabase();
    }

    // Save user data in the database (CSV file)
private:
    void SimulateDatabase()
    {
        ofstream outFile;
        outFile.open("Database.csv", ios::app); // Open in append mode

        if (outFile.is_open())
        {
            // Write user data in CSV format (without header)
            outFile << username << ","
                    << password << ","
                    << Email << ","
                    << DOB << ","
                    << RegistrationDate << "\n";

            outFile.close();
            cout << GREEN << "[Success] " << RESET << " User data has been saved to Database.csv." << endl;
        }
        else
        {
            cerr << RED << "[Error] " << RESET << " Unable to open the file!" << endl;
        }
    }

public:
    void SimulateUserData(PassiveIncome passobj, ActiveIncome actobj, Income incobj,
                          FixedExpenditure fixedobj, VariableExpenditure varobj,
                          Expenditure expobj, Budget budobj, Assets assetobj)
    {
        if (!isLoggedin)
        {
            cout << YELLOW << "[Prompt] " << RESET << " Please Log in !!!" << endl;
            return;
        }

        ofstream outFile("UserData.csv", ios::app); // Open in append mode
        if (!outFile.is_open())
        {
            cerr << RED << "[Error] " << RESET << " Error opening the User Data file for writing!" << endl;
            return;
        }

        // Calculate the maximum size to ensure all vectors are accounted for
        int maxSize = max({
            passobj.Passive_income_stream_Amount.size(),
            actobj.Active_income_stream_Amount.size(),
            fixedobj.Fixed_Expenditure_Amount.size(),
            varobj.Variable_Expenditure_Amount.size(),
            budobj.Amount.size(),
            assetobj.Asset_List.size() // Include asset list size in max calculation
        });

        for (int i = 0; i < maxSize; ++i)
        {
            // Write the basic user info
            outFile << username << "," << Email << ",";

            // Passive income section
            if (i < passobj.Passive_income_stream_Amount.size())
            {
                outFile << passobj.Passive_income_stream_names[i] << ","
                        << passobj.Passive_income_stream_date[i] << ","
                        << passobj.Passive_income_stream_Amount[i] << ",";
            }
            else
            {
                outFile << "N/A,N/A,0,";
            }

            // Active income section
            if (i < actobj.Active_income_stream_Amount.size())
            {
                outFile << actobj.Active_income_stream_names[i] << ","
                        << actobj.Active_incom_stream_date[i] << ","
                        << actobj.Active_income_stream_Amount[i] << ",";
            }
            else
            {
                outFile << "N/A,N/A,0,";
            }

            // Taxes
            incobj.CopyPassiveIncome(passobj);
            incobj.CopyActiveIncome(actobj);
            incobj.CalculateTaxes('N');
            outFile << incobj.returntaxes() << ",";

            // Fixed expenditure section
            if (i < fixedobj.Fixed_Expenditure_Amount.size())
            {
                outFile << fixedobj.Fixed_Expenditure_Name[i] << ","
                        << fixedobj.Fixed_Expenditure_Date[i] << ","
                        << fixedobj.Fixed_Expenditure_Amount[i] << ",";
            }
            else
            {
                outFile << "N/A,N/A,0,";
            }

            // Variable expenditure section
            if (i < varobj.Variable_Expenditure_Amount.size())
            {
                outFile << varobj.Variable_Expenditure_Name[i] << ","
                        << varobj.Variable_Expenditure_Date[i] << ","
                        << varobj.Variable_Expenditure_Amount[i] << ",";
            }
            else
            {
                outFile << "N/A,N/A,0,";
            }

            // Total expenditure
            expobj.CopyFixedExpenditure(fixedobj);
            expobj.CopyVariableExpenditure(varobj);
            outFile << expobj.CalculateTotalExpenditure('N') << ",";

            // Budget section
            budobj.Copy(fixedobj, varobj);
            if (i < budobj.Amount.size())
            {
                outFile << budobj.Category[i] << "," << budobj.Amount[i] << ",";
            }
            else
            {
                outFile << "N/A,0,";
            }

            // Asset section
            if (i < assetobj.Asset_List.size())
            {
                Asset &currentAsset = assetobj.Asset_List[i];
                outFile << currentAsset.getName() << ","
                        << currentAsset.getQuantity() << ","
                        << currentAsset.getAcquisitionCost() << ","
                        << currentAsset.getAcquisitionDate() << ","
                        << currentAsset.getLiquidity() << ","
                        << currentAsset.getCurrentValue() << ","
                        << currentAsset.getCurrentDate() << ","
                        << currentAsset.getGrowthRate();
            }
            else
            {
                outFile << "N/A,0,0,N/A,0,0,N/A,0";
            }

            outFile << "\n";
        }

        // Close the file
        outFile.close();
    }

    // Check if a user is already registered (based on username or email)
    bool isUserRegistered(const string &username, const string &email)
    {
        ifstream inFile("Database.csv");

        if (inFile.is_open())
        {
            string line, fileUsername, fileEmail;

            getline(inFile, line); // Skip the header row

            // Read each line to check if the username or email is already registered
            while (getline(inFile, line))
            {
                stringstream ss(line);
                getline(ss, fileUsername, ','); // Get the username
                ss.ignore(256, ',');            // Skip the password field
                getline(ss, fileEmail, ',');    // Get the email

                if (fileUsername == username || fileEmail == email)
                {
                    return true; // User already exists
                }
            }

            inFile.close();
        }
        else
        {
            cerr << RED << "[Error]  " << "Unable to open the file for reading!" << endl;
        }

        return false; // User not found
    }

    void DisplayUserData()
    {
        if (!isLoggedin)
        {
            cout << RED << "[Error] " << RESET << "You are not logged in." << endl;
            return;
        }

        ifstream inFile("UserData.csv");
        if (!inFile.is_open())
        {
            cerr << RED << "[Error] " << RESET << "Unable to open UserData.csv for reading!" << endl;
            return;
        }

        string line;
        getline(inFile, line); // Skip header line

        vector<vector<string>> userDataLines;
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string usernameField;
            getline(ss, usernameField, ',');

            if (usernameField == username)
            {
                vector<string> fields;
                fields.push_back(usernameField);
                string field;
                while (getline(ss, field, ','))
                {
                    fields.push_back(field);
                }
                userDataLines.push_back(fields);
            }
        }
        inFile.close();

        if (userDataLines.empty())
        {
            cout << RED << "[Error] " << RESET << "No data found for the current user." << endl;
            return;
        }

        const vector<string> fieldNames = {
            "Username", "Email", "Passive Stream Name", "Passive Stream Date", "Passive Stream Amount",
            "Active Stream Name", "Active Stream Date", "Active Stream Amount", "Total Tax",
            "Fixed Expenditure Name", "Fixed Expenditure Date", "Fixed Expenditure Amount",
            "Variable Expenditure Name", "Variable Expenditure Date", "Variable Expenditure Amount",
            "Total Expenditure", "Budget Category", "Budget Amount",
            "Asset Name", "Asset Quantity", "Asset Acquisition Cost", "Asset Acquisition Date",
            "Asset Liquidity", "Asset Current Value", "Asset Current Date", "Asset Growth Rate"};

        cout << "+" << string(90, '-') << "+" << endl;
        for (const auto &userData : userDataLines)
        {
            for (size_t i = 0; i < fieldNames.size() && i < userData.size(); ++i)
            {
                cout << "| " << left << setw(30) << fieldNames[i] << "| " << setw(58) << userData[i] << " |" << endl;
            }
            cout << "+" << string(90, '-') << "+" << endl;
        }
    }

    void ClearData()
    {
        if (!isLoggedin)
        {
            cout << RED << "[Error] " << RESET << "You are not logged in. Unable to clear data." << endl;
            return;
        }

        ifstream inFile("UserData.csv");
        ofstream outFile("TempUserData.csv");

        if (!inFile.is_open() || !outFile.is_open())
        {
            cerr << RED << "[Error] " << RESET << " Unable to open UserData.csv for reading!" << endl;
            return;
        }

        string line;
        getline(inFile, line);
        outFile << line << endl;

        while (getline(inFile, line))
        {
            stringstream ss(line);
            string usernameField;
            getline(ss, usernameField, ',');

            if (usernameField != username)
            {
                outFile << line << endl;
            }
        }

        inFile.close();
        outFile.close();

        remove("UserData.csv");
        rename("TempUserData.csv", "UserData.csv");

        cout << GREEN << "[Success]  " << "User data has been cleared successfully." << endl;
    }

public:
    bool LogIn(PassiveIncome &passObj, ActiveIncome &actObj,
               Income &incObj, FixedExpenditure &fixedObj,
               VariableExpenditure &varObj, Expenditure &expObj,
               Budget &budObj, Assets &assetObj)
    {
        string inputUsername, inputPassword;
        cout << YELLOW << "[Prompt] " << RESET << "Enter username: ";
        getline(cin >> ws, inputUsername);
        cout << YELLOW << "[Prompt] " << RESET << "Enter password: ";
        getline(cin >> ws, inputPassword);

        ifstream inFile("Database.csv");
        if (inFile.is_open())
        {
            string line;
            getline(inFile, line); // Skip the header row
            while (getline(inFile, line))
            {
                stringstream ss(line);
                string storedUsername, storedPassword, storedEmail, storedDOB, storedRegDate;

                getline(ss, storedUsername, ',');
                if (ss.peek() == ',')
                    ss.ignore();
                getline(ss, storedPassword, ',');
                if (ss.peek() == ',')
                    ss.ignore();
                getline(ss, storedEmail, ',');
                if (ss.peek() == ',')
                    ss.ignore();
                getline(ss, storedDOB, ',');
                if (ss.peek() == ',')
                    ss.ignore();
                getline(ss, storedRegDate);

                if (storedUsername == inputUsername && storedPassword == inputPassword)
                {
                    username = storedUsername;
                    password = storedPassword;
                    Email = storedEmail;
                    DOB = storedDOB;
                    RegistrationDate = storedRegDate;
                    isLoggedin = true;
                    inFile.close();
                    cout << GREEN << "[Success] " << RESET << " Login successful!" << endl;
                    LoadUserData(passObj, actObj, incObj, fixedObj, varObj, expObj, budObj, assetObj);
                    return true;
                }
            }
            inFile.close();
        }
        else
        {
            cerr << RED << "[Error] " << RESET << " Unable to open the file for reading!" << endl;
        }
        cout << RED << "[Error] " << RESET << " Invalid Username or password." << endl;
        return false;
    }

    void UpdateProfile()
    {
        if (!isLoggedin)
        {
            cout << RED << "[Error] " << RESET << "You are not logged in." << endl;
            return;
        }
        else
        {
            cout << "Update Profile" << endl;
            cout << "1. Update Email" << endl;
            cout << "2. Update Username" << endl;
            cout << "3. Update Password" << endl;
            cout << "4. Update Date of Birth" << endl;
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            string oldValue, newValue;
            switch (choice)
            {
            case 1:
                oldValue = Email;
                Email = validate('E');
                newValue = Email;
                break;
            case 2:
                oldValue = username;
                username = validate('U');
                newValue = username;
                break;
            case 3:
                oldValue = password;
                password = validate('P');
                newValue = password;
                break;
            case 4:
                oldValue = DOB;
                DOB = validate('D');
                newValue = DOB;
                break;
            default:
                cout << RED << "[Error]" << "Invalid choice." << endl;
                return;
            }

            UpdateDatabaseFile(oldValue, newValue, choice);
        }
    }

    void UpdateDatabaseFile(const string &oldValue, const string &newValue, int field)
    {
        ifstream inFile("Database.csv");
        ofstream outFile("TempDatabase.csv");

        if (inFile.is_open() && outFile.is_open())
        {
            string line;
            getline(inFile, line); // Read and write the header
            outFile << line << endl;

            while (getline(inFile, line))
            {
                stringstream ss(line);
                string fileUsername, filePassword, fileEmail, fileDOB, fileRegDate;

                getline(ss, fileUsername, ',');
                getline(ss, filePassword, ',');
                getline(ss, fileEmail, ',');
                getline(ss, fileDOB, ',');
                getline(ss, fileRegDate);

                if (fileUsername == username)
                {
                    switch (field)
                    {
                    case 1:
                        fileEmail = newValue;
                        break;
                    case 2:
                        fileUsername = newValue;
                        break;
                    case 3:
                        filePassword = newValue;
                        break;
                    case 4:
                        fileDOB = newValue;
                        break;
                    }
                }

                outFile << fileUsername << "," << filePassword << "," << fileEmail << "," << fileDOB << "," << fileRegDate << endl;
            }

            inFile.close();
            outFile.close();

            remove("Database.csv");
            rename("TempDatabase.csv", "Database.csv");

            cout << GREEN << "[Success]  " << "Profile updated successfully!" << endl;
        }
        else
        {
            cerr << "Unable to open files for updating!" << endl;
        }
    }

    void ViewProfile()
    {
        if (!isLoggedin)
        {
            cout << RED << "[Error] " << RESET << "You are not logged in." << endl;
            return;
        }

        cout << "+" << string(50, '-') << "+" << endl;
        cout << "| " << left << setw(20) << "Field"
             << "| " << setw(27) << "Details" << "|" << endl;
        cout << "+" << string(50, '-') << "+" << endl;

        cout << "| " << left << setw(20) << "Username"
             << "| " << setw(27) << username << "|" << endl;
        cout << "| " << left << setw(20) << "Email"
             << "| " << setw(27) << Email << "|" << endl;
        cout << "| " << left << setw(20) << "Date of Birth"
             << "| " << setw(27) << DOB << "|" << endl;
        cout << "| " << left << setw(20) << "Registration Date"
             << "| " << setw(27) << RegistrationDate << "|" << endl;

        cout << "+" << string(50, '-') << "+" << endl;
    }

    void LogOut()
    {
        cout << GREEN << "[Success]" << RESET << " Successfully Logged out." << endl;
        isLoggedin = false;
    }
    friend class FinanceHub;

    static bool isFileEmpty(const string &fileName)
    {
        ifstream inFile(fileName);
        return inFile.peek() == ifstream::traits_type::eof();
    }

    static void CreateUserDataDatabase()
    {
        if (isFileEmpty("UserData.csv"))
        {
            ofstream outFile("UserData.csv", ios::app);
            if (outFile.is_open())
            {
                outFile << "Username,Email,PassiveStreamName,PassiveStreamDate,PassiveStreamAmount,"
                           "ActiveStreamName,ActiveStreamDate,ActiveStreamAmount,"
                           "TotalTax,FixedExpenditureName,FixedExpenditureDate,FixedExpenditureAmount,"
                           "VariableExpenditureName,VariableExpenditureDate,VariableExpenditureAmount,"
                           "TotalExpenditure,BudgetCategory,BudgetAmount,"
                           "AssetName,AssetQuantity,AssetAcquisitionCost,AssetAcquisitionDate,"
                           "AssetLiquidity,AssetCurrentValue,AssetCurrentDate,AssetGrowthRate\n";
                isUserdataDatabaseCreated = true;
                cout << GREEN << "[Success] " << RESET << " UserData.csv has been created." << endl;
                outFile.close();
            }
            else
            {
                cerr << RED << "[Error] " << RESET << " Unable to create UserData.csv!" << endl;
            }
        }
        else
        {
            cout << GREEN << "[Success] " << RESET << " UserData.csv already exists, skipping header creation." << endl;
        }
    }

    static void CreateDatabase()
    {
        if (isFileEmpty("Database.csv"))
        {
            ofstream outFile("Database.csv", ios::app);
            if (outFile.is_open())
            {
                outFile << "Username,Password,Email,DOB,RegistrationDate\n";
                isDatabaseCreated = true;
                cout << GREEN << "[Success] " << RESET << " Database.csv has been created." << endl;
                outFile.close();
            }
            else
            {
                cerr << RED << "[Error] " << RESET << " Unable to create Database.csv!" << endl;
            }
        }
        else
        {
            cout << GREEN << "[Success] " << RESET << " Database.csv already exists, skipping header creation." << endl;
        }
    }

    void LoadUserData(PassiveIncome &passObj, ActiveIncome &actObj,
                      Income &incObj, FixedExpenditure &fixedObj,
                      VariableExpenditure &varObj, Expenditure &expObj,
                      Budget &budObj, Assets &assetObj)
    {
        ifstream infile("UserData.csv");

        if (infile.is_open())
        {
            string line;
            while (getline(infile, line))
            {
                stringstream ss(line);
                string item;

                if (!getline(ss, item, ',') || item != username)
                    continue;

                getline(ss, item, ','); // Email

                // Passive Income
                string passiveStreamName, passiveStreamDate;
                double passiveStreamAmount;
                getline(ss, passiveStreamName, ',');
                getline(ss, passiveStreamDate, ',');
                getline(ss, item, ',');
                stringstream(item) >> passiveStreamAmount;
                passObj.Passive_income_stream_names.push_back(passiveStreamName);
                passObj.Passive_income_stream_date.push_back(passiveStreamDate);
                passObj.Passive_income_stream_Amount.push_back(passiveStreamAmount);

                // Active Income
                string activeStreamName, activeStreamDate;
                double activeStreamAmount;
                getline(ss, activeStreamName, ',');
                getline(ss, activeStreamDate, ',');
                getline(ss, item, ',');
                stringstream(item) >> activeStreamAmount;
                actObj.Active_income_stream_names.push_back(activeStreamName);
                actObj.Active_incom_stream_date.push_back(activeStreamDate);
                actObj.Active_income_stream_Amount.push_back(activeStreamAmount);

                // Total Tax
                getline(ss, item, ',');
                stringstream(item) >> incObj.tax;

                // Fixed Expenditure
                string fixedExpName, fixedExpDate;
                double fixedExpAmount;
                getline(ss, fixedExpName, ',');
                getline(ss, fixedExpDate, ',');
                getline(ss, item, ',');
                stringstream(item) >> fixedExpAmount;
                fixedObj.Fixed_Expenditure_Name.push_back(fixedExpName);
                fixedObj.Fixed_Expenditure_Date.push_back(fixedExpDate);
                fixedObj.Fixed_Expenditure_Amount.push_back(fixedExpAmount);

                // Variable Expenditure
                string varExpName, varExpDate;
                double varExpAmount;
                getline(ss, varExpName, ',');
                getline(ss, varExpDate, ',');
                getline(ss, item, ',');
                stringstream(item) >> varExpAmount;
                varObj.Variable_Expenditure_Name.push_back(varExpName);
                varObj.Variable_Expenditure_Date.push_back(varExpDate);
                varObj.Variable_Expenditure_Amount.push_back(varExpAmount);

                // Total Expenditure
                getline(ss, item, ',');
                stringstream(item) >> expObj.total_expenditure;

                // Budget
                string budgetCategory;
                double budgetAmount;
                getline(ss, budgetCategory, ',');
                getline(ss, item, ',');
                stringstream(item) >> budgetAmount;
                budObj.Category.push_back(budgetCategory);
                budObj.Amount.push_back(budgetAmount);

                // Asset
                string assetName, assetQuantity, assetAcquisitionCost, assetAcquisitionDate;
                string assetLiquidity, assetCurrentValue, assetCurrentDate, assetGrowthRate;
                getline(ss, assetName, ',');
                getline(ss, assetQuantity, ',');
                getline(ss, assetAcquisitionCost, ',');
                getline(ss, assetAcquisitionDate, ',');
                getline(ss, assetLiquidity, ',');
                getline(ss, assetCurrentValue, ',');
                getline(ss, assetCurrentDate, ',');
                getline(ss, assetGrowthRate);

                Asset newAsset;
                newAsset.setValues(assetName,
                                   stoi(assetQuantity),
                                   stod(assetAcquisitionCost),
                                   assetAcquisitionDate,
                                   stod(assetLiquidity),
                                   stod(assetCurrentValue),
                                   assetCurrentDate,
                                   stod(assetGrowthRate));
                assetObj.Asset_List.push_back(newAsset);
            }
        }
        else
        {
            cerr << RED << "[Error]" << RESET << " Unable to open UserData.csv file!" << endl;
        }
    }
};

// Initialize static members
bool User::isDatabaseCreated = false;
bool User::isUserdataDatabaseCreated = false;

class FinanceHub
{
    PassiveIncome Pa;
    ActiveIncome Ac;
    Income Inc;
    FixedExpenditure Fe;
    VariableExpenditure Ve;
    Expenditure Ex;
    Budget Bu;
    Assets Asset;
    User Us;

    void PassiveIncome()
    {
        int choice;
        bool exitMenu = false;

        while (!exitMenu)
        {
            cout << CYAN << "\nPassive Income Operations:\n"
                 << RESET;
            cout << BLUE << "1. Record\n";
            cout << "2. Modify\n";
            cout << "3. Operations\n";
            cout << "4. Display\n";
            cout << "5. Reset\n";
            cout << "0. Back to Main Menu\n";
            cout << YELLOW << "[Prompt] " << RESET << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                Pa.RecordPassiveIncome();
                break;
            case 2:
                Pa.ModifyPassiveIncome();
                break;
            case 3:
                Pa.OperationOnPassiveIncome();
                break;
            case 4:
                Pa.DisplayPassiveIncome();
                break;
            case 5:
                Pa.Reset();
                break;
            case 0:
                exitMenu = true;
                break;
            default:
                cout << RED << "[Error] " << RESET << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }

    void ActiveIncome()
    {
        int choice;
        bool exitMenu = false;

        while (!exitMenu)
        {
            cout << CYAN << "\nActive Income Operations:\n"
                 << RESET;
            cout << BLUE << "1. Record\n";
            cout << "2. Modify\n";
            cout << "3. Operations\n";
            cout << "4. Display\n";
            cout << "5. Reset\n";
            cout << "0. Back to Main Menu\n";
            cout << YELLOW << "[Prompt] " << RESET << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                Ac.RecordActiveIncome();
                break;
            case 2:
                Ac.ModifyActiveIncome();
                break;
            case 3:
                Ac.OperationOnActiveIncome();
                break;
            case 4:
                Ac.DisplayActiveIncome();
                break;
            case 5:
                Ac.Reset();
                break;
            case 0:
                exitMenu = true;
                break;
            default:
                cout << RED << "[Error] " << RESET << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }

    void Income()
    {
        int choice;
        bool exitMenu = false;

        while (!exitMenu)
        {
            cout << CYAN << "\nIncome Operations:\n\n"
                 << RESET;
            cout << BLUE << "1. Copy Streams to Income\n";
            cout << "2. Calculate Taxes\n";
            cout << "3. Sort\n";
            cout << "4. Generate Report\n";
            cout << "5. Reset\n";
            cout << "6. Commit changes to Passive and Active streams\n";
            cout << "0. Back to Main Menu\n";
            cout << YELLOW << "[Prompt] " << RESET << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                Inc.CopyPassiveIncome(Pa);
                Inc.CopyActiveIncome(Ac);
                cout << GREEN << "[Success] " << RESET << "Copied data successfully!\n";
                break;
            case 2:
                Inc.CalculateTaxes('Y');
                break;
            case 3:
                Inc.Sort();
                break;
            case 4:
                Inc.GenerateReport();
                break;
            case 5:
                Inc.Reset();
                break;
            case 6:
                Inc.Commit(Pa, Ac);
                break;
            case 0:
                exitMenu = true;
                break;
            default:
                cout << RED << "[Error] " << RESET << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }

    void FixedExpenditure()
    {
        int choice;
        bool exitMenu = false;

        while (!exitMenu)
        {
            cout << CYAN << "\nFixed Expenditure Operations:\n\n"
                 << RESET;
            cout << BLUE << "1. Record\n";
            cout << "2. Modify\n";
            cout << "3. Operations\n";
            cout << "4. Display\n";
            cout << "5. Reset\n";
            cout << "0. Back to Main Menu\n";
            cout << YELLOW << "[Prompt] " << RESET << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                Fe.RecordFixedExpenditure();
                break;
            case 2:
                Fe.ModifyFixedExpenditure();
                break;
            case 3:
                Fe.OperationsOnFixedExpenditure();
                break;
            case 4:
                Fe.DisplayFixedExpenditures();
                break;
            case 5:
                Fe.Reset();
                break;
            case 0:
                exitMenu = true;
                break;
            default:
                cout << RED << "[Error] " << RESET << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }

    void VariableExpenditure()
    {
        int choice;
        bool exitMenu = false;

        while (!exitMenu)
        {
            cout << CYAN << "\nVariable Expenditure Operations:\n\n"
                 << RESET;
            cout << BLUE << "1. Record\n";
            cout << "2. Modify\n";
            cout << "3. Operations\n";
            cout << "4. Display\n";
            cout << "5. Reset\n";
            cout << "0. Back to Main Menu\n";
            cout << YELLOW << "[Prompt] " << RESET << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                Ve.RecordVariableExpenditure();
                break;
            case 2:
                Ve.ModifyVariableExpenditure();
                break;
            case 3:
                Ve.OperationsOnVariableExpenditure();
                break;
            case 4:
                Ve.DisplayVariableExpenditures();
                break;
            case 5:
                Ve.Reset();
                break;
            case 0:
                exitMenu = true;
                break;
            default:
                cout << RED << "[Error] " << RESET << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }

    void Expenditure()
    {
        int choice;
        bool exitMenu = false;

        while (!exitMenu)
        {
            cout << CYAN << "\nExpenditure Operations:\n\n"
                 << RESET;
            cout << BLUE << "1. Copy Streams to Expenditure\n";
            cout << "2. Calculate Total Expenditure\n";
            cout << "3. Sort\n";
            cout << "4. Generate Report\n";
            cout << "5. Reset\n";
            cout << "6. Commit changes to Passive and Active Streams\n";
            cout << "0. Back to Main Menu\n";
            cout << YELLOW << "[Prompt] " << RESET << "Enter Your Choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                Ex.CopyFixedExpenditure(Fe);
                Ex.CopyVariableExpenditure(Ve);
                cout << GREEN << "[Success] " << RESET << "Copied Data Successfully!\n";
                break;
            case 2:
                Ex.CalculateTotalExpenditure('Y');
                break;
            case 3:
                Ex.Sort();
                break;
            case 4:
                Ex.GenerateExpenditureReport();
                break;
            case 5:
                Ex.Reset();
                break;
            case 6:
                Ex.Commit(Fe, Ve);
                break;
            case 0:
                exitMenu = true;
                break;
            default:
                cout << RED << "[Error] " << RESET << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }

    void Budget()
    {
        int choice;
        bool exitMenu = false;

        while (!exitMenu)
        {
            cout << CYAN << "\nBudget Operations:\n\n"
                 << RESET;
            cout << BLUE << "1. Copy Expenses in Budget object\n";
            cout << "2. Record Budget\n";
            cout << "3. Perform Operations on Budget\n";
            cout << "4. Reset Budget\n";
            cout << "0. Back to Main Menu\n";
            cout << YELLOW << "[Prompt] " << RESET << "Enter Your Choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                Bu.Copy(Fe, Ve);
                cout << GREEN << "[Success] " << RESET << "Copied Data Successfully!\n";
                break;
            case 2:
                Bu.RecordBudget();
                break;
            case 3:
                Bu.OperationsonBudget();
                break;
            case 4:
                Bu.ResetBudget();
                break;
            case 0:
                exitMenu = true;
                break;
            default:
                cout << RED << "[Error] " << RESET << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }

    void Assets()
    {
        int choice;
        bool exitMenu = false;

        while (!exitMenu)
        {
            cout << CYAN << "\nAssets Operations:\n\n"
                 << RESET;
            cout << BLUE << "1. Record Assets\n";
            cout << "2. Modify Assets\n";
            cout << "3. Filter Assets\n";
            cout << "4. Display Assets\n";
            cout << "5. Reset Assets\n";
            cout << "6. Show Portfolio of Assets\n";
            cout << "0. Back to Main Menu\n";
            cout << YELLOW << "[Prompt] " << RESET << "Enter Your Choice: ";

            cin >> choice;

            switch (choice)
            {
            case 1:
                Asset.RecordAssetes();
                break;
            case 2:
                Asset.ModifyAsstes();
                break;
            case 3:
                Asset.FilterAsstess();
                break;
            case 4:
                Asset.DisplayAsstes();
                break;
            case 5:
                Asset.ResetAssets();
                break;
            case 6:
                Asset.ShowPortfolio();
                break;
            case 0:
                exitMenu = true;
                break;
            default:
                cout << RED << "[Error] " << RESET << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }

    void Users()
    {
        int choice;
        bool exitMenu = false;

        while (!exitMenu)
        {
            cout << CYAN << "\nUser Application Operations:\n\n"
                 << RESET;
            cout << BLUE << "1. Register\n";
            cout << "2. Log In\n";
            cout << "3. Update Profile\n";
            cout << "4. View Profile\n";
            cout << "5. Display User Data\n";
            cout << "6. Clear Data\n";
            cout << "7. Simulate User Data\n";
            cout << "8. Log out\n";
            cout << "0. Back to Main Menu\n";
            cout << YELLOW << "[Prompt] " << RESET << "Enter Your Choice: ";

            cin >> choice;

            switch (choice)
            {
            case 1:
                Us.Register();
                break;
            case 2:
                Us.isLoggedin = Us.LogIn(Pa, Ac, Inc, Fe, Ve, Ex, Bu, Asset);
                break;
            case 3:
                Us.UpdateProfile();
                break;
            case 4:
                Us.ViewProfile();
                break;
            case 5:
                Us.DisplayUserData();
                break;
            case 6:
                Us.ClearData();
                break;
            case 7:
                Us.SimulateUserData(Pa, Ac, Inc, Fe, Ve, Ex, Bu, Asset);
                break;
            case 8:
                Us.LogOut();
                break;
            case 0:
                exitMenu = true;
                break;
            default:
                cout << RED << "[Error] " << RESET << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }

public:
    void Menu()
    {
        int choice;
        do
        {
            cout << "\n"
                 << GREEN << "========================================" << RESET << endl;
            cout << GREEN << "|            Finance Hub Menu          |" << RESET << endl;
            cout << GREEN << "========================================" << RESET << endl;

            cout << YELLOW << "[Prompt] " << RESET << "1. Manage Passive Income\n";
            cout << YELLOW << "[Prompt] " << RESET << "2. Manage Active Income\n";
            cout << YELLOW << "[Prompt] " << RESET << "3. Manage Income\n";
            cout << YELLOW << "[Prompt] " << RESET << "4. Manage Fixed Expenditures\n";
            cout << YELLOW << "[Prompt] " << RESET << "5. Manage Variable Expenditures\n";
            cout << YELLOW << "[Prompt] " << RESET << "6. Manage Expenditures\n";
            cout << YELLOW << "[Prompt] " << RESET << "7. Manage Budget\n";
            cout << YELLOW << "[Prompt] " << RESET << "8. Manage Assets\n";
            cout << YELLOW << "[Prompt] " << RESET << "9. Manage User Profile\n";
            cout << YELLOW << "[Prompt] " << RESET << "0. Exit\n";

            cout << YELLOW << "Enter your choice: " << RESET;
            cin >> choice;

            switch (choice)
            {
            case 1:
                PassiveIncome();
                break;
            case 2:
                ActiveIncome();
                break;
            case 3:
                Income();
                break;
            case 4:
                FixedExpenditure();
                break;
            case 5:
                VariableExpenditure();
                break;
            case 6:
                Expenditure();
                break;
            case 7:
                Budget();
                break;
            case 8:
                Assets();
                break;
            case 9:
                Users();
                break;
            case 0:
                cout << GREEN << "[Success] " << RESET << "Exiting the program.\n";
                break;
            default:
                cout << RED << "[Error] " << RESET << "Invalid choice. Please try again.\n";
                break;
            }
        } while (choice != 0);
    }
};

int main()
{
    User User1;
    User1.CreateDatabase();
    User1.CreateUserDataDatabase();

    FinanceHub Fb;
    Fb.Menu();

    return 0;
}