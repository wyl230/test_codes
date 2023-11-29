def test(a=[]):
    print(id(a))

    a.append(1)
    print(a)


test()
test()
test()
