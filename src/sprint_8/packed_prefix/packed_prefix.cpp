/*              --- ПРИНЦИП РАБОТЫ ---
 *   Для нахождения наибольшего общего префикса строится первая
 * строка, она же записывается как исходный общий префикс, а остальные
 * посимвольно сравниваются с ней в процессе распаковки. При
 * обнаружении расхождения процесс распаковки очередной строки
 * завершается, как новый общий префикс записывается подстрока от
 * предыдущего от начала до расхождения.
 *   Функции построения строки и распаковки со сравнением имеют в
 * основе одну логику, за исключением того, что при распаковке со
 * сравнением вместо дополнения строки происходит, собственно,
 * сравнение. Прицип работы следующий: посимвольно распаковывается
 * (и сверяется или дополняется префикс) исходная строка, пока не
 * встречается цифра. Когда встречается цифра, считывается число
 * повторов и происходит переход на следующий уровень рекурсии. Когда
 * встречается закрывающая скобка, происходит возврат на предыдущий
 * уровень рекурсии и символы для повтора шаблона берутся из уже
 * проитерированных по префиксной строке ранее, так как уже известно,
 * где шаблон начался и где закончился.
 *
 *              --- ВРЕМЕННАЯ СЛОЖНОСТЬ ---
 *   Первая строка строится целиком, по всем остальным итерации
 * заканчиваются на первом отличающемся символе для каждой строки.
 * Таким образом в худшем случае, когда распакованные строки будут
 * идентичны сложность по времени составит O(n*m), где n - количество
 * строк, а m - их длина в распакованном виде. Для общего случая
 * сложность составит O(n*x), где n - снова количество строк, а x -
 * средняя длина общего префикса.
 *
 *              --- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ ---
 *   Дополнительная память нужна только для хранения первой
 * распакованной строки, таким образом, пространственная сложность
 * составит O(l), где l - длина первой строки в распакованном виде.
 */

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

int build_recursive(
        const std::string& from,
        std::string& to,
        int& f_pos,
        int& to_pos)
{
    for (;f_pos < from.size();) {
        if (std::isdigit(from[f_pos])) {
            std::string times;
            for (;std::isdigit(from[f_pos]); ++f_pos)
                times.push_back(from[f_pos]);
            ++f_pos; // skip '['
            int t = std::stoi(times)-1;
            int to_start = to_pos; // pattern begins here and ends \/
            int fin = build_recursive(from, to, f_pos, to_pos); // here
            // repeat unpacked pattern t-1 times
            for (int j = to_start; t > 0; --t, j = to_start) {
                for (;j < fin; ++to_pos, ++j) {
                    to.push_back(to[j]);
                }
            }
            continue;
        }
        if (from[f_pos] == ']') {
            ++f_pos; // skip ']'
            return to_pos;
        }
        to.push_back(from[f_pos]);
        ++f_pos, ++to_pos;
    }
    return to_pos;
}

std::pair<int, bool> unpack_recursive(
        const std::string& s,
        const std::string& built,
        int& i,
        int& built_pos)
{
    for (; i < s.size() && built_pos < built.size();)
    {
        if (std::isdigit(s[i])) {
            std::string times;
            for (;std::isdigit(s[i]); ++i)
                times.push_back(s[i]);
            ++i; // skip '['
            int t = std::stoi(times) - 1;
            int b_start = built_pos;
            auto [fin, stop] = unpack_recursive(s,built,i,built_pos);
            if (stop)
                return {fin, stop};

            for (int j = b_start; t > 0; --t, j = b_start) {
                for (;j < fin; ++built_pos, ++j) {
                    if (built[j] != built[built_pos])
                        return {built_pos, true};
                }
            }
            continue;
        }
        if (s[i] == ']') {
            ++i;
            return {built_pos, false};
        }
        if (s[i] != built[built_pos]) {
            return {built_pos, true};
        }
        ++i, ++built_pos;
    }
    return {built_pos, false};
}

std::string build(const std::string& s)
{
    std::string to;
    int s_cur = 0, to_cur = 0;
    build_recursive(s, to, s_cur, to_cur);
    return to;
}

int unpack(const std::string& s, const std::string& built_str)
{
    int s_cur = 0, built_cur = 0;
    return unpack_recursive(s, built_str, s_cur, built_cur).first;
}

std::string get_max_prefix(const std::vector<std::string>& strs)
{
    std::string unpacked = build(strs[0]);
    for (int i = 1; i < strs.size(); ++i) {
        int fin = unpack(strs[i], unpacked);
        unpacked = unpacked.substr(0, fin);
    }

    return unpacked;
}

int main()
{
    int t = 0;
    std::cin >> t;
    for (;t-->0;){
        int strings_num;
        std::cin >> strings_num;
        std::vector<std::string> strs(strings_num);

        for (auto& s: strs)
            std::cin >> s;

        std::cout << get_max_prefix(strs) << std::endl;
    }

    return 0;
}
