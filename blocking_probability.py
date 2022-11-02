import math
import matplotlib.pyplot as plt


def erlang_probability(A, m):
    numerator = (A**m) / math.factorial(m)
    sum = 0

    for n in range(m+1):
        sum += (A**n)/math.factorial(n)

    return(numerator/sum)


def main():
    channels = 19
    offered_load = 1

    CHANNELS = []

    PB_all = []

    for i in range(19):
        CHANNELS.append(i)

    for i in range(1, 10):
        for j in range(1, channels+1):
            PB = erlang_probability(i, j)
            PB_all.append(PB)

    chunked_list = list()
    chunk_size = 19

    for i in range(0, len(PB_all), chunk_size):
        chunked_list.append(PB_all[i:i+chunk_size])

    denom_sum = 0

    # for i in range(channels):
    #     numerator = (offered_load**channels)/math.factorial(channels)
    #     denom = (offered_load**i)/math.factorial(i)
    #     denom_sum = denom_sum + denom
    #     PB_1.append(numerator/denom_sum)

    print(chunked_list)

    plt.plot(CHANNELS, chunked_list[0])
    plt.show()


if __name__ == "__main__":
    main()
