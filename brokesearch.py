
def broken_search(nums, target) -> int:
    return broke_search(0, len(nums)-1, nums, target)

def broke_search(l_bound, r_bound, a_list, target) -> int:
    mid = (r_bound + l_bound)//2
    lb_value = a_list[l_bound]
    rb_value = a_list[r_bound]
    mid_value = a_list[mid]
    print(f'l_bound {l_bound}, r_bound {r_bound}, mid {mid}')
    print(f'l_bound val {lb_value}, r_bound val {rb_value}, mid v {mid_value}')
    if target == mid_value:
        return mid
    if target > rb_value and target < lb_value:
        return -1
    if lb_value < mid_value and mid_value < rb_value:
        return binary_search(l_bound, r_bound, a_list, target)
    if mid_value <= rb_value:
        if target > mid_value and target <= rb_value:
            print('call binary_search')
            return binary_search(mid+1, r_bound, a_list, target)
        else:
            return broke_search(l_bound, mid-1, a_list, target)
    elif mid_value > lb_value:
        if target < mid_value and target > lb_value:
            print('call binary_search')
            return binary_search(l_bound, mid-1, a_list, target)
        else:
            return broke_search(mid+1, r_bound, a_list, target)    




def binary_search(l_bound, r_bound, a_list, target) -> int:
    mid = (r_bound + l_bound)//2
    mid_value = a_list[mid]
    print(f'l_bound {l_bound}, r_bound {r_bound}, mid {mid}')
    if target == mid_value:
        return mid
    if l_bound >= r_bound or target > a_list[r_bound] or target < a_list[l_bound]:
        return -1
    if target > mid_value:
        return binary_search(mid+1, r_bound, a_list, target)
    else:
        return binary_search(l_bound, mid-1, a_list, target)

def test():
    arr = [19, 21, 100, 101, 1, 4, 5, 7, 12]
    print(f'final {broken_search(arr, 101)}')
    # assert broken_search(arr, 4) == 5

if __name__ == '__main__':
    test()