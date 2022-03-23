import random

def partitioning(array, pivot):
    left = [i for i in array if i < pivot]
    center = [i for i in array if i == pivot]
    right = [i for i in array if i > pivot]
    return left, center, right

def quicksort(array):
    if len(array) < 2:
        return array
    else:
        pivot = array[random.randint(0, len(array)-1)]
        left, center, right = partitioning(array, pivot)
        left = quicksort(left)
        right = quicksort(right)
        return left + center + right

def test():
    arr = [19, 21, 100, 101, 1, 4, 5, 7, 12]
    narr = arr.sort()
    print(quicksort(arr))
    print(narr)
    # assert quicksort(arr) == narr

if __name__ == '__main__':
    test()