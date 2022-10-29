import math
from wsgiref.simple_server import demo_app


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

    PB_1 = []
    PB_2 = []
    PB_3 = []
    PB_4 = []
    PB_5 = []
    PB_6 = []
    PB_7 = []
    PB_8 = []
    PB_9 = []
    PB_10 = []

    for i in range(19):
        CHANNELS.append(i)

    for i in range(1, 10):
        for j in range(1, channels):
            PB = erlang_probability(i, j)
            PB_all.append(PB)

    denom_sum = 0

    # for i in range(channels):
    #     numerator = (offered_load**channels)/math.factorial(channels)
    #     denom = (offered_load**i)/math.factorial(i)
    #     denom_sum = denom_sum + denom
    #     PB_1.append(numerator/denom_sum)

    print(PB_all)
    # print(PB_1)
    # print(PB_2)
    # print(PB_3)
    # print(PB_4)
    # print(PB_5)
    # print(PB_6)
    # print(PB_7)
    # print(PB_8)
    # print(PB_9)
    # print(PB_10)


if __name__ == "__main__":
    main()
