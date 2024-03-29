import numpy
import pylab

bin_str = '0001111100000011000000001100000000110000001111110000011100100000110000000011000000001100000001100100'
lines = open('memories/memories.txt', 'r').readlines()
lines_corr = open('memories_corrupted.txt', 'r').readlines()

def PrintImageNumber(a):
    for i in numpy.ndarray.flatten(a):
        print(i,end='')
    print()

def MakeFace():
    face=numpy.zeros((10,10),int)
    face[9,0]=1
    face[8,1]=1
    face[7,2]=1
    face[6,3]=1
    face[6,4]=1
    face[6,5]=1
    face[7,6]=1
    face[8,7]=1
    face[8,8]=1
    face[9,9]=1
    face[1,3]=1
    face[1,7]=1
    face[4,4]=1
    return face


def MakeTree():
    tree=numpy.zeros((10,10),int)
    for i in range(0,10):
        tree[i,4]=1
        tree[i,5]=1
    for i in range(3,7):
        tree[1,i]=1
        tree[0,i]=1

    for i in range(2,9):
        tree[4,i]=1
    tree[5,8]=1
    return tree

def MakeImage(neurons):
    bin_arr = numpy.zeros((100,1))
    for i in range(0, len(neurons)):
        bin_arr[i] = neurons[i]
    bin_arr = bin_arr.reshape((10,10))
    return bin_arr

for line in zip(lines, lines_corr):
    myImg = MakeImage(line[0].strip())
    print("This is the binary representation of my image")
    print(bin_str)
    pylab.matshow(myImg)
    pylab.title("Here we go")
    pylab.show()

    myImg = MakeImage(line[1].strip())
    print("This is the binary representation of my image")
    print(bin_str)
    pylab.matshow(myImg)
    pylab.title("Here we go")
    pylab.show()
    
face=MakeFace()
print("This is the binary representation of the face")
PrintImageNumber(face)
pylab.matshow(face)
pylab.title("I was supposed to be a \n happy face but I got the curvature wrong")
pylab.show()

#tree=MakeTree()
#print("This is the binary representation of the tree")
#PrintImageNumber(tree)
#pylab.matshow(tree)
#pylab.title("I am the best artistic rendition \n of a tree that Bryan could handle.")
#pylab.show()


