//функция provider_sequence получает в качестве аргументов массивы - данные по поставщикам одного определенного продукта
// и возвращает строку в которой через запятую указаны индексы поставщиков по порядку, у которых необходимо закупать этот товар для достижения максимальной выгоды.
// Аргументы:
// n - количество товара, который необходимо закупить
// price - массив цен за партию товара у поставщиков
// amount  - массив количества товаров в партии
// count - количество партий, находящихся у поставщика
// delivery - стоимость доставки(данная функция считает доставку фиксированной в независимости от того, сколько товара/партий будет доставлено)
//
//
//
string provider_sequence(int n, vector<int> price, vector<int> amount, vector<int> count, vector<int> delivery)//функция выдающая строку с индексами поставщиков, в порядке, в котором следует осуществлять закупку
{
    vector<double> priceForOne(price.size()); //массив цен за одну единицу товара
    vector<bool> restProviders(price.size(), true); //массив с отметками поставщиков, у котороых закупка еще не осуществлялась
    int i;
    int j;
    double minPriceForOne; //минимальная цена за единицу
    int provider; //индекс поставщика обладающего минимальной ценой за единицу товара
    string answer; //строка с перечислением индексов поставщиков
    int providers = price.size(); //количество оставшихся поставщиков, у которых закупка еще не осуществлялась
    double summ = 0;
    int N; //специальное количество товара для расчета стоимости за единицу

    while (n > 0 && providers != 0) //заказываем по очереди с самой дешевой ценой
    { 
        for (i = 0; i < price.size(); i++) //Высчитываем стоимость товара за единицу (каждую новую итерацию)
        {

            if (amount[i] * count[i] <= n) N = n; //высчитываем N
            if (amount[i] * count[i] > n)
            {
                N = 0;
                j = 0;
                while (N < n && j <= count[i])
                {
                    N += amount[i];
                    j++;
                }
            }
            priceForOne[i] = 1.0 * price[i] / amount[i] + 1.0 * delivery[i] / N;

            summ += priceForOne[i];
        }
        providers--;
        minPriceForOne = summ;
        for (i = 0; i < price.size(); i++)//вычисляем выгоднейшую цену за единицу для данной итерации
        {
            if (priceForOne[i] < minPriceForOne && restProviders[i])
            {
                minPriceForOne = priceForOne[i];
                provider = i;
            }
        }
        restProviders[provider] = false;
        n -= amount[provider] * count[provider]; //подсчитываем сколько еще надо купить товара
        if (n > 0 && providers != 0) answer = answer + to_string(provider) + ",";
        if (n <= 0 || providers == 0) answer = answer + to_string(provider);
    }
    return answer;
}