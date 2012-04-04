# prepare the Covtype dataset for training and testing

def process_covtype():
    dfile = open('covtype.data')
    lines = dfile.readlines()
    dfile.close()
    lines_train = lines[0:387342]
    lines_test = lines[387343:581012]
    train_file = open('covtype.train', 'w')
    train_file.writelines(lines_train)
    train_file.close()
    test_file = open('covtype.test', 'w')
    test_file.writelines(lines_test)
    test_file.close()


if __name__ == '__main__':
    process_covtype()
