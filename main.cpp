#include<iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <windows.h>
#include <algorithm>
#include <ctime>

using namespace std;

string remove_zeroes(string str_with_zeroes) {
    string str = move(str_with_zeroes);
    reverse(str.begin(), str.end());
    bool remove = false;
    for (auto c:str) {
        if (c == '.' || c == ',') {
            remove = true;
            break;
        }
    }
    if (remove) {
        for (auto &c : str) {
            if (c == '0' || c == '.' || c == ',') {
                if (c == '.' || c == ',') {
                    c = '\0';
                    break;
                } else {
                    c = '\0';
                }
            } else {
                break;
            }
        }
    }
    reverse(str.begin(), str.end());
    string output;
    for (char i : str)
        if (i != '\0') output += i;
    return output;
}

double max_func(double a, double b) {
    if (a > b) return a;
    return b;
}

double min_func(double a, double b) {
    if (a < b) return a;
    return b;
}

bool isNumeric(string str) {
    int index = 0, number_of_commas = 0, minus_index = 0;
    for (char &c : remove_zeroes(str)) {
        if (c == '-') {
            minus_index++;
        } else {
            break;
        }
    }
    if (minus_index % 2 == 0) {
        str.erase(0, minus_index);
    } else {
        str.erase(0, minus_index - 1);
    }
    for (char &c : remove_zeroes(str)) {
        if (isdigit(c) == 0) {
            if (c != '\0') {
                if ((c != '.' && c != ',') || number_of_commas >= 1) {
                    if (c == '-') {
                        if (index != 0) {
                            return false;
                        }
                    } else {
                        return false;
                    }
                }
            }
            if (c == '.' || c == ',') {
                number_of_commas++;
            }
        }
        index++;
    }
    return true;
}

void SetColor(int color) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, color);
}

static int padding = 0;

void print_text(string text) {
    int month_to_find_color = 110;
    int day_to_find_color = 79;
    int default_color = 7;
    bool highlight_d = false;
    bool highlight_m = false;
    for (int char_index = 0; char_index < text.size(); char_index++) {
        if (text[char_index] == '%') {
            if (text[char_index + 1] == '\'') {
                switch (text[char_index + 2]) {
                    case 'a':
                        cout << (char) 133;
                        break;
                    case 'e':
                        cout << (char) 138;
                        break;
                    case 'i':
                        cout << (char) 141;
                        break;
                    case 'o':
                        cout << (char) 149;
                        break;
                    case 'u':
                        cout << (char) 151;
                        break;
                    default:
                        break;
                }
                char_index += 2;
            } else if (text[char_index + 1] == 'n') {
                cout << "dei ";
                char_index += 2;
            } else if (text[char_index + 1] == 's') {
                cout << "un numero ";
                char_index += 2;
            } else if (text[char_index + 1] == 'v') {
                cout << "varie volte ";
                char_index += 2;
            } else if (text[char_index + 1] == '%') {
                cout << "%";
            } else if (text[char_index + 1] == 'c') {
                switch (text[char_index + 2]) {
                    case 'd':
                        highlight_d = true;
                        break;
                    case 'm':
                        highlight_m = true;
                        break;
                    case 'e':
                        highlight_d = false;
                        highlight_m = false;
                        SetColor(default_color);
                        break;
                }
                char_index += 2;
            }
        } else {
            if (text[char_index - 1] == '\n' || highlight_m && text[char_index - 4] == '\n') {
                for (int i = 0; i < padding; i++) {
                    cout << " ";
                }
            }
            if (highlight_d) {
                SetColor(day_to_find_color);
            } else if (highlight_m) {
                SetColor(month_to_find_color);
            }
            cout << text[char_index];

        }
    }
}

double string_to_double(string str) {
    string num_str;
    int minus_index = 0;
    bool negative = false, comma_found = false;
    for (char &c : remove_zeroes(str)) {
        if (c == '-') {
            minus_index++;
        } else {
            break;
        }
    }
    if (minus_index % 2 == 0) {
        str.erase(0, minus_index);
    } else {
        str.erase(0, minus_index - 1);
    }
    for (char &c : remove_zeroes(str)) {
        if (isdigit(c) == 0) {
            if (c == '.' || c == ',' || c == '-') {
                if (c != '-') {
                    if (c == ',') {
                        c = '.';
                    }
                    num_str += c;
                } else {
                    negative = true;
                }
            }
        } else {
            num_str += c;
        }
    }
    reverse(num_str.begin(), num_str.end());
    int numbers_before_comma = 0, index, i, local_precision = 0;
    double num = 0;
    for (char c: num_str) {
        if (c == '.' || c == ',') {
            comma_found = true;
            break;
        }
        numbers_before_comma--;
    }
    if (comma_found) {
        index = numbers_before_comma;
    } else {
        index = 0;
    }
    for (char c: num_str) {
        i = (int) c - '0';
        if (c != '.' && c != ',') {
            num += i * pow(10, index);
            index++;
            local_precision++;
        }
    }
    if (negative) {
        num = -num;
    }
    return num;
}


bool isInteger(double number) {
    if (remove_zeroes(to_string(number)).find('.') == -1) {
        return true;
    }
    return false;
}


int input_manager(const string &ex_str, const string &str_input, const string &conditions = "",
                  double condition_value[] = nullptr) {

    string temp_str;
    string temp_output_double;
    double temp_num;
    bool error;
    int condition_count;
    string temp;
    auto input_error = [](const string &temp, string ex_str, const string &temp_str, double temp_num,
                          const string &string_error) {
        print_text(string_error);
        system("pause");
        system("CLS");
        print_text(std::move(ex_str));
    };
    do {
        temp = str_input;
        error = false;
        cout << temp;
        cin >> temp_output_double;
        if (!isNumeric(temp_output_double)) {
            input_error(temp_str, ex_str, temp_output_double, temp_num,
                        "\nIl valore inserito %'e errato\n\n");
            error = true;
            cin.ignore(10000, '\n');
        } else {
            temp_num = string_to_double(temp_output_double);
            if (!conditions.empty()) {
                condition_count = 0;
                for (char condition: conditions) {
                    if (condition == '<') {
                        if (temp_num > condition_value[condition_count]) {
                            input_error(temp_str, ex_str, temp_output_double, temp_num,
                                        "\nIl valore inserito %'e errato, devi inserire un valore minore a " +
                                        remove_zeroes(to_string(condition_value[condition_count])) + "!\n\n");
                            error = true;
                            cin.ignore(10000, '\n');
                        }
                    } else if (condition == '>') {
                        if (temp_num < condition_value[condition_count]) {
                            input_error(temp_str, ex_str, temp_output_double, temp_num,
                                        "\nIl valore inserito %'e errato, devi inserire un valore maggiore a " +
                                        remove_zeroes(to_string(condition_value[condition_count])) + "!\n\n");
                            error = true;
                            cin.ignore(10000, '\n');
                        }
                    }
                    condition_count++;
                }
            }
            if (!error) {
                if (!isInteger(temp_num)) {
                    input_error(temp_str, ex_str, temp_output_double, temp_num,
                                "\nIl valore inserito %'e errato, puoi solo inserire interi!\n\n");
                    error = true;
                    cin.ignore(10000, '\n');
                } else {
                    temp_num = (int) temp_num;
                    cout << "Valore inserito:	" << temp_num << endl << endl;
                    error = false;
                }
            }
        }
    } while (error);
    return (int) temp_num;
}


int main() {
    HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
    string month[] = {"Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno", "Luglio", "Agosto", "Settembre",
                      "Ottobre", "Novembre", "Dicembre"};
    string week_real[] = {"Lu", "Ma", "Me", "Gi", "Ve", "Sa", "Do"};
    string week_fake[] = {"Ve", "Sa", "Do", "Lu", "Ma", "Me", "Gi"};
    int month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days = 365;
    const string real_first_day = "Venerd%'i";
    const int real_year = 2021;
    int year;
    int global_counter;
    int day_counter = 1;
    int column_counter = 0;
    int last_column_counter = 0;
    int day_month_counter = 0;
    int change_day_counter;
    int differenza_anni;
    int first_day = 0;
    bool change_month = false;
    bool to_find = false;
    int month_to_find;
    int day_to_find;
    string calendar;
    string es_temp = "Questo programma chiede all'utente se vuole creare un calendario o ricercare una data di un certo anno.";
    string es_temp_1 = "Questo programma realizza un calendario avendo come input solo l'anno.";
    string es_temp_2 = "Questo programma realizza un calendario ed effettua la ricerca di una data inserita dall'utente.";
    string es_temp_3 = "Questo programma realizza il calendario dell'anno corrente.";
    string actions = es_temp + "\n\nAzioni possibili:\n"
                               "1) Realizzazione di un calendario dato l'anno\n"
                               "2) Realizzazione di un calendario dato l'anno e ricerca del giorno inserito\n"
                               "3) Realizzazione del calendario dell'anno corrente\n";
    print_text(actions);
    int type = input_manager(actions, "\nSeleziona una scelta:	", "><", new double[2]{0, 4});
    system("CLS");
    if (type == 1) {
        es_temp = es_temp_1;
    } else if (type == 2) {
        es_temp = es_temp_2;
    } else {
        es_temp = es_temp_3;
    }
    print_text(es_temp);
    if (type != 3) {
        year = input_manager(es_temp, "\n\nInserisci un anno:	");
        if (year % 4 == 0) {
            month_days[1]++;
            days++;
        }
        es_temp += "\n\nAnno da analizzare:	" + to_string(year) + "\n";
        if (type == 2) {
            to_find = true;
            system("CLS");
            print_text(es_temp);
            month_to_find = input_manager(es_temp, "\n\nInserisci il mese da cercare in forma numerica:	", "><",
                                          new double[2]{0, 12}) - 1;
            system("CLS");
            es_temp += "Mese selezionato:	" + month[month_to_find];
            print_text(es_temp);
            day_to_find = input_manager(es_temp, "\n\nInserisci il giorno da cercare in forma numerica:	", "><",
                                        new double[2]{0, (double) month_days[month_to_find]});
            system("CLS");
        }
    } else {
        to_find = true;
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        year = 1900 + ltm->tm_year;
        month_to_find = ltm->tm_mon;
        day_to_find = ltm->tm_mday;
    }
    if (to_find) {
        print_text("\n\nAnno da analizzare:	" + to_string(year) + "\n");
        print_text("Il mese da cercare %'e " + month[month_to_find] + "\n");
        print_text("Il giorno da cercare %'e " + to_string(day_to_find) + "\n");
    }
    padding = 36;
    global_counter = 0;
    differenza_anni = (int) abs(real_year - year);
    for (int i = (int) min_func(real_year, year);
         i < max_func(real_year, year); i++) {
        if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0) {
            differenza_anni++;
        }
    }
    change_day_counter = 0;
    for (int i = 0; i < differenza_anni; i++) {
        if (real_year < year) {

            change_day_counter++;
            if (change_day_counter >= 7) {
                change_day_counter = 0;
            }

        } else if (real_year > year) {
            change_day_counter--;
            if (change_day_counter < 0) {
                change_day_counter = 6;
            }
        }
    }
    differenza_anni = change_day_counter;
    for (int i = 0; i < 7; i++) {
        if (week_real[i] == week_fake[differenza_anni]) {
            first_day = i;
            break;
        }
    }
    if (day_month_counter == month_to_find && to_find) {
        calendar += ("\n%cm     ----------------" + month[day_month_counter] + "----------------     %ce\n");
    } else {
        calendar += ("\n     ----------------" + month[day_month_counter] + "----------------     \n");
    }
    calendar += "\n  Lu     Ma     Me     Gi     Ve     Sa     Do \n\n";
    do {
        if (global_counter >= first_day) {
            if (day_counter > month_days[day_month_counter]) {
                day_month_counter++;
                day_counter = 1;
                calendar += "\n";
                calendar += "\n";
                if (day_month_counter == month_to_find && to_find) {
                    calendar += ("%cm     ----------------" + month[day_month_counter] + "----------------     %ce");
                } else {
                    calendar += ("     ----------------" + month[day_month_counter] + "----------------     ");
                }

                calendar += "\n";
                calendar += ("\n  Lu     Ma     Me     Gi     Ve     Sa     Do \n\n");
                last_column_counter = column_counter;
                column_counter = 0;
                change_month = true;
            }
            if (!change_month || last_column_counter == 7) {
                change_month = false;
                if (column_counter >= 7) {
                    column_counter = 0;
                    calendar += "\n";
                }

                if (day_counter < 10) {
                    calendar += "  ";
                    if (day_month_counter == month_to_find && day_to_find == day_counter && to_find) {
                        calendar += "%cd " + to_string(day_counter) + "%ce";
                    } else {
                        calendar += " " + to_string(day_counter);
                    }

                    calendar += "   ";
                } else {
                    calendar += "  ";
                    if (day_month_counter == month_to_find && day_to_find == day_counter && to_find) {
                        calendar += "%cd" + to_string(day_counter) + "%ce";
                    } else {
                        calendar += to_string(day_counter);
                    }
                    calendar += "   ";
                }

                day_counter++;
            } else {

                if (column_counter >= last_column_counter - 1) {
                    change_month = false;
                }
                calendar += "       ";
                first_day++;
            }
        } else {
            calendar += "       ";
        }
        column_counter++;
        global_counter++;
    } while (global_counter <= days + first_day - 1);
    print_text(calendar);
    cout << endl;
    system("PAUSE");
    return 0;
}
