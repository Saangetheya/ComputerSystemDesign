import os
import os.path as path
import cv2 as cv
import numpy as np
import sys

stdout = sys.stdout

image_paths = os.listdir(path.join(os.getcwd(), 'images'))


def conv_image_file(filepath, output_path, count):
    img = cv.imread(filepath, cv.IMREAD_GRAYSCALE)
    # change size of image preserving aspec ratio

    containsone = filepath.find("1") != -1

    # calculate mode in the np array
    max = 0
    dict = {}

    for row in img:
        for col in row:
            if col in dict:
                dict[col] += 1
            else:
                dict[col] = 1

            if dict[col] > max:
                max = col

    height, width = img.shape
    if height > width:
        img = cv.resize(img, (int(128 * width / height), 128))
    else:
        img = cv.resize(img, (128, int(128 * height / width)))

    height, width = img.shape
    if height < 128:
        img = np.append(img, max*np.ones((128 - height, width)), axis=0)
    if width < 128:
        img = np.append(img, max*np.ones((128, 128 - width)), axis=1)

    img = np.uint8(img)
    # img = cv.resize(img, (128, 128))
    # img = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
    # img = cv.adaptiveThreshold(img, 255, cv.ADAPTIVE_THRESH_GAUSSIAN_C,
    # cv.THRESH_BINARY, 5, 2)
    # img = cv.GaussianBlur(img, (3, 3), 0)

    img = cv.Canny(img, 40, 200)
    _, img = cv.threshold(img, 100, 255, cv.THRESH_BINARY, img)
    if containsone:
        img = cv.bitwise_not(img)
    cv.imwrite(output_path, img)

    content = np.array(img)
    initial_content = "char font_{}[{}][{}] = {{\n".format(
        count, len(content), int(len(content[0])/8))

    def reverse(num):
        result = 0
        for i in range(8):
            result = result << 1
            result += (num & 1)
            num = num >> 1
        return result

    for c, row in enumerate(content):
        initial_content += "\t{"
        value = 0
        for cc, col in enumerate(row):
            value = value << 1
            value += (1 if col == 255 else 0)
            if cc % 8 == 7:
                value = reverse(value)
                initial_content += "{}".format(value)
                value = 0
                if cc != len(row) - 1:
                    initial_content += ", "
        initial_content += "}"
        if c != len(content) - 1:
            initial_content += ",\n"
    initial_content += "\n};\n"

    with open("./out/face_{}.h".format(count), "w") as f:
        f.write(initial_content)


if __name__ == "__main__":
    for c, filepath in enumerate(image_paths):
        conv_image_file("./images/{}".format(filepath),
                        "./out/face_{}.jpg".format(c), c)
