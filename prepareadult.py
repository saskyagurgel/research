# prepare the Adult dataset for training and testing

def process_adult():
    dfile = open('adult.data')
    lines = dfile.readlines()
    dfile.close()
    lines_train = lines[0:21708]
    lines_test = lines[21709:32562]
    train_file = open('adult.train', 'w')
    train_file.writelines(lines_train)
    train_file.close()
    test_file = open('adult.test', 'w')
    test_file.writelines(lines_test)
    test_file.close()


if __name__ == '__main__':
    process_adult()
