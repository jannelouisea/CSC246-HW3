list1 = [1,2,3]
list2 = [10,11]
list3 = 100
combos = list()
tcombos = list()

# 10 & 11

for i in range(0,len(list1)+1):
  newlist = list()
  newlist.extend(list1)
  newlist.insert(i, list2[0])
  newlist.insert(i+1, list2[1])
  combos.append(newlist)

# 10 then 11

N = len(list1) + 1
for n in range(N, 1, -1):
  i10 = N-n
  # print 'i10: ' + str(i10)
  for j in range(1, n):
    # print 'j: ' + str(j)
    i11 = i10+1+j
    # print 'i11: ' + str(i11)
    newlist = list()
    newlist.extend(list1)
    newlist.insert(i10, list2[0])
    newlist.insert(i11, list2[1])
    # print newlist
    combos.append(newlist)

for clist in combos:
  # print clist
  for i in range(0, len(clist)):
    newlist = list()
    newlist.extend(clist)
    newlist.insert(i, list3)
    tcombos.append(newlist)

# print '================================='

for tlist in tcombos:
  print tlist


