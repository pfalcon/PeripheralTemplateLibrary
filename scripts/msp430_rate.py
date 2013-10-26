def calc(freq, baud):
    return ((freq * 8 * 2 / baud) - (freq / baud * 8 * 2) + 1) / 2

#for baud in (9600, 19200, 38400, 56000, 115200, 128000, 256000):

MOD = [0, 0x02, 0x22, 0x2a, 0xaa, 0xae, 0xee, 0xfe]


for baud in (256000,):
    div = 1000000 / baud
    mod = calc(1000000, baud) + 0
    print baud, mod
    t_ideal = 1.0 / baud
    print "ideal bit length (s):", t_ideal
    bit = 1
    err = 0.0
    while bit != 0x100:
        t = (div + int(bool(MOD[mod] & bit))) / 1000000.0
        print t, t - t_ideal
        err += t - t_ideal
        bit <<= 1

    print err / t_ideal * 100
