from helper import read_data


def init_table():
    table_dict = {}
    table_str = """\
|   AA  |   ɑ   |     P     |  p  |     S     |  s  |
|   AE  |   æ   |     B     |  b  |     SH    |  ʃ  |
|   AH  |   ʌ   |     CH    |  tʃ |     T     |  t  |
|   AO  |   ɔ   |     D     |  d  |     TH    |  θ  |
|   AW  |   aʊ  |     DH    |  ð  |     V     |  v  |
|   AY  |   aɪ  |     F     |  f  |     W     |  w  |
|   EH  |   ɛ   |     G     |  g  |     Y     |  j  |
|   ER  |   ɜːr |     HH    |  h  |     Z     |  z  |
|   EY  |   eɪ  |     JH    |  dʒ |     ZH    |  ʒ  |
|   IH  |   ɪ   |     K     |  k  |           |     |
|   IY  |   i   |     L     |  l  |           |     |
|   OW  |   oʊ  |     M     |  m  |           |     |
|   OY  |   ɔɪ  |     N     |  n  |           |     |
|   UH  |   ʊ   |     NG    |  ŋ  |           |     |
|   UW  |   u   |     R     |  r  |           | $ $ |"""
    table_list = list(filter(lambda x: not x in "$$\n",
                             table_str.replace(" ", "").split("|")))
    for x in range(int(len(table_list) / 2)):
        table_dict[table_list[2 * x]] = table_list[2 * x + 1]
    return table_dict


replace_table = init_table()


def replace_each_symbol(each_symbol):
    if each_symbol in replace_table:
        return replace_table[each_symbol]
    else:
        return each_symbol


def to_ipa(symbol_str):
    symbol_str = symbol_str.replace(
        "0", "").replace("1", " '").replace("2", ",")
    return "".join([replace_each_symbol(each_symbol) for each_symbol in symbol_str.split(" ")])


def process_line(line):
    word, pronunciatin = line.split(':')
    return word + ":" + to_ipa(pronunciatin)


data = read_data("./asset/training_data.txt")
data = list([process_line(line) for line in data])

with open("./asset/training_data.txt" + ".new", mode='w', encoding="UTF-8") as out:
    out.write("\n".join(data))
