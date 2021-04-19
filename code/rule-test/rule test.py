def hamming_distance_rate(li1, li2):
    diff_cnt = 0
    total_size = len(li1)*len(li1[0])
    for i in range(len(li1)):
        for j in range(len(li1[0])):
            if li1[i][j] != li2[i][j]:
                diff_cnt += 1
    return diff_cnt / total_size
    


pair_input = ['zero_box']
pair_output = []

f = open("rt_pair.txt", 'r')
lines = f.readlines()

matrix = list()
for line in lines:
    if(len(line)-1 == 6):    # if this line is input_bits
        pair_input.append(line[:-1])
        pair_output.append(matrix)
        matrix = list()
    else:
        matrix.append(line[:-1])
pair_output.append(matrix)

pair_input.pop(0)
pair_output.pop(0)

# 겹치는 부분 제거하기
for x in set(pair_input):
    for i in range(pair_input.count(x)-1):
        idx = pair_input.index(x)
        pair_input.pop(idx)
        pair_output.pop(idx)

print(" li1  li2    rate")
print('-'*20)
avg_diff_rate = 0
for i in range(0, len(pair_input)):
    for j in range(0, i):
        if(i==j):
            continue
        diff_rate = hamming_distance_rate(pair_output[i], pair_output[j])
        avg_diff_rate += diff_rate
        if(diff_rate<0.35):
            print("%4d"%i,"%4d"%(j),"  %.3lf DANGER"%diff_rate)
        elif(diff_rate<0.4):
            print("%4d"%i,"%4d"%(j),"  %.3lf WARNING"%diff_rate)
#        else:
#            print("%4d"%i,"%4d"%(i+1),"  %.3lf"%diff_rate)

avg_diff_rate /= len(pair_input)-1
print("average rate: %.4lf"%avg_diff_rate)

f.close()

