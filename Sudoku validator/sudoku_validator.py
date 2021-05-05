import numpy
def valid_solution(board):
    res=True
    cnt=0
    board=numpy.asarray(board)
    for i in board:
        bo1=check_row(i)
        col=board[:,cnt]
        bo2=check_row(col)
        res=res and bo1 and bo2
        if(res==False):
            return res
        cnt+=1
    num=0
    while num<=26:
        f=board[3*(num//9):3+3*(num//9),num %9 :3+num%9].flatten()
        res=res and check_row(f)
        num=num+3
        if(res==False):
            return res
    return res
def check_row(row):
    sortd=numpy.sort(row)
    com=numpy.array([1,2,3,4,5,6,7,8,9])
    r=numpy.array_equal(sortd,com)
    return r


a=valid_solution([[5, 3, 4, 6, 7, 8, 9, 1, 2], ##example, returns true
                  [6, 7, 2, 1, 9, 5, 3, 4, 8],
                  [1, 9, 8, 3, 4, 2, 5, 6, 7],
                  [8, 5, 9, 7, 6, 1, 4, 2, 3],
                  [4, 2, 6, 8, 5, 3, 7, 9, 1],
                  [7, 1, 3, 9, 2, 4, 8, 5, 6],
                  [9, 6, 1, 5, 3, 7, 2, 8, 4],
                  [2, 8, 7, 4, 1, 9, 6, 3, 5],
                  [3, 4, 5, 2, 8, 6, 1, 7, 9]])



