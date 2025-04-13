#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

// Define stock structure
typedef struct stock
{
    char name[10];
    struct tm date;
    long long price;
} Stock;

void predictPrice()
{
    const char *stockNames[] = {"tesla", "reliance", "adani", "tata", "apple"};
    time_t now = time(NULL);

    for (int j = 0; j < 5; j++)
    {
        Stock stocks[5];
        long long maxProfit = 0;
        int buyIndex = 0, sellIndex = 0;

        // Generate 5 days of prices for 1 stock
        for (int i = 0; i < 5; i++)
        {
            time_t future = now + i * 86400;
            struct tm *date = localtime(&future);

            strncpy(stocks[i].name, stockNames[j], sizeof(stocks[i].name) - 1);
            stocks[i].name[sizeof(stocks[i].name) - 1] = '\0';
            stocks[i].date = *date;
            stocks[i].price = (rand() % 1000000) + 50000;

            printf("Stock: %s | Date: %02d-%02d-%04d | Price: %lld\n",
                   stocks[i].name,
                   stocks[i].date.tm_mday,
                   stocks[i].date.tm_mon + 1,
                   stocks[i].date.tm_year + 1900,
                   stocks[i].price);
        }

        // Calculate max profit
        for (int buy = 0; buy < 5; buy++)
        {
            for (int sell = buy + 1; sell < 5; sell++)
            {
                long long profit = stocks[sell].price - stocks[buy].price;
                if (profit > maxProfit)
                {
                    maxProfit = profit;
                    buyIndex = buy;
                    sellIndex = sell;
                }
            }
        }

        printf("\n>>> Stock: %s\n", stockNames[j]);
        if (maxProfit > 0)
        {
            printf("Max Profit: %lld\n", maxProfit);
            printf("Buy Date : %02d-%02d-%04d (Price: %lld)\n",
                   stocks[buyIndex].date.tm_mday,
                   stocks[buyIndex].date.tm_mon + 1,
                   stocks[buyIndex].date.tm_year + 1900,
                   stocks[buyIndex].price);
            printf("Sell Date: %02d-%02d-%04d (Price: %lld)\n",
                   stocks[sellIndex].date.tm_mday,
                   stocks[sellIndex].date.tm_mon + 1,
                   stocks[sellIndex].date.tm_year + 1900,
                   stocks[sellIndex].price);
        }
        else
        {
            printf("No profit possible in the given 5 days.\n");
        }

        printf("-------------------------------------------------\n\n");
    }
}

int main()
{
    srand(time(NULL));
    predictPrice();
    return 0;
}
