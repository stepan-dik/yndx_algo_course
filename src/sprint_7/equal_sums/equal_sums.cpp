/*              --- ПРИНЦИП РАБОТЫ ---
 *   Задача сводится к задаче о рюкзаке, где значения чисел
 * одновременно являются и их весами, и их ценностью, а за
 * "максимальную вместимость" берётся целевое значение, то есть
 * половина суммы всех элементов.
 *   В двумерном массиве dp хранятся суммы лучших комбинаций для
 * префиксов массива. Базовых случаев для задачи существует по
 * количеству элементов исходного массива + 1, при нулевой вместимости
 * их ценность будет равна 0, также как и для случая без значений при
 * любой вместимости.
 *   Переходом динамики будет максимум из двух величин:
 * - Лучшее значение для комбинации без рассматриваемого элемента,
 * - Ценность рассматриваемого элемента и лучшее значение для
 * комбинации без рассматриваемого элемента при вместимости равной
 * разнице между текущей и весом рассматриваемого элемента.
 *   Матрица заполняется построчно для каждого элемента исходного
 * массива.
 *   Так как нет необходимости вывести непосредственно комбинацию, при
 * которой достижимо целевое значение, достаточно хранить
 * обрабатываемую строку массива и предыдущую, вся матрица не
 * хранится.
 *
 *              --- ВРЕМЕННАЯ СЛОЖНОСТЬ ---
 *   Каждая ячейка условной матрицы размером N*M (где M - полусумма от
 * всех элементов исходного массива, N - количество элементов
 * исходного массива) посещается и считается один раз, формируя таким
 * образом сложность по времени O(N*M).
 *
 *              --- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ ---
 *   Так как вместо полной матрицы в реализованном алгоритме
 * используется только 2 строки, в худшем случае, пространственная
 * сложность составит O(n), где n полусумма всех элементов исходного
 * массива.
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Using 2 lines of matrix
bool has_equal_sums_1(const std::vector<int>& results)
{
    int sum = 0;
    for (const auto& i: results)
        sum += i;    
    if (sum % 2 != 0)
        return false;
    int half = sum / 2;
    std::vector<std::vector<int>> dp(2, std::vector<int>(half+1, 0));
    for (unsigned int i = 1; i < results.size()+1; ++i) {
        std::swap(dp[0], dp[1]);
        for (int j = 1; j < dp[1].size(); ++j) {
            if (j - results[i-1] >= 0) {
                dp[1][j] = std::max(dp[0][j],
                        results[i-1] + dp[0][j - results[i-1]]);
            }
            else
                dp[1][j] = dp[0][j];
        }
    }
    std::cout << sum << " " << half;
    return dp[1][half] == half;
}

// Using 1 line of matrix
bool has_equal_sums_2(std::vector<int>& results)
{
    std::sort(results.begin(), results.end());
    int sum = 0;
    for (const auto& i: results)
        sum += i;
    if (sum % 2 != 0)
        return false;
    int half = sum / 2;
    std::vector<int> dp(half + 1, 0);
    int max_sum = 0;
    for (unsigned int i = 1; i < results.size()+1; ++i) {
        int cur_val = results[i-1];
        max_sum += cur_val;
        for (int j = 1; j < dp.size(); ++j) {
            if (j - cur_val >= 0 && j < max_sum)
                dp[j] = std::max(dp[j], cur_val + dp[j - cur_val]);
            else if (j >= max_sum)
                dp[j] = max_sum;
        }
    }
    return dp[half] == half;
}

// Using vector<bool> with available sums and buffered indices to change
bool has_equal_sums_3(const std::vector<int>& results)
{
    int sum = 0;
    for (const auto& i: results)
        sum += i;
    if (sum % 2 != 0)
        return false;
    int half = sum / 2;
    std::vector<bool> dp(half+1, false);
    dp[0] = true;
    for (const auto& val: results) {
        std::vector<int> to_change;
        for (int i = 1; i < dp.size(); ++i) {
            if (i - val >= 0 && dp[i-val])
                to_change.push_back(i);
        }
        for (const auto& j: to_change)
            dp[j] = true;
        if (dp[half])
            break;
    }
    for (const auto& i: dp)
        std::cout << i << " ";
    return dp[half];
}

/*              --- ПРИНЦИП РАБОТЫ ---
 *   Задача сводится к задаче о рюкзаке, где значения чисел
 * одновременно являются и их весами, и их ценностью, а за
 * "максимальную вместимость" берётся целевое значение, то есть
 * половина суммы всех элементов.
 *   В массиве dp хранятся булевые значения, в которые мы записываем,
 * достижимо ли значение по весу текущего индекса, при использовании
 * уже рассмотренных элементов и текущего. Базовых случаев для задачи
 * существует по количеству элементов исходного массива + 1, нулевая
 * сумма по умолчанию задаётся как достижимая.
 *   Переходом динамики будет проверка достижимости значения путём
 * проверки возможности получения разницы целевой суммы и текущего
 * элемента исходного массива. Для того, чтобы избежать возможного
 * двойного использования одного и того же элемента при формировании
 * достижимых значений, проход по массиву достижимых значений
 * происходит с конца.
 *   Итерации продолжаются, пока последний элемент массива достижимых
 * значений не станет true, либо пока пока массив значений не
 * закончится.
 *
 *              --- ВРЕМЕННАЯ СЛОЖНОСТЬ ---
 *   Для каждого элемента массива исходных значений величиной N
 * посещается каждый элемент массива достижимых значений величиной M,
 * формируя таким образом сложность по времени O(N*M).
 *
 *              --- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ ---
 *   Так как в реализованном алгоритме используется одномерный массив,
 * хранящий количество элементов, равное полусумме значений всех
 * элементов исходного массива, пространственная сложность составит
 * O(n), где n полусумма всех элементов исходного массива.
 */

// Using vector<bool> with available sums and going backwards
bool has_equal_sums_4(const std::vector<int>& results)
{
    int sum = 0;
    for (const auto& i: results)
        sum += i;
    if (sum % 2 != 0)
        return false;
    int half = sum / 2;
    std::vector<bool> dp(half+1, false);
    dp[0] = true;
    for (const auto& val: results) {
        for (int i = dp.size(); i-- > 0; ) {
            if (i - val >= 0) {
                dp[i] = dp[i] || dp[i-val];
            }
        }
        if (dp[half])
            break;
    }

    return dp[half];
}

int main()
{
    int n = 0;
    std::cin >> n;
    std::vector<int> results(n);
    for (auto& r: results)
        std::cin >> r;

    std::cout << (has_equal_sums_4(results) ? "True" : "False") << std::endl;

    return 0;
}
