from cs50 import get_string
from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""

    # TODO
    first = a.split("\n")
    second = b.split("\n")
    first_set = set(first)
    second_set = set(second)
    ourset = set(first_set).intersection(second_set)
    return ourset


def sentences(a, b):
    """Return sentences in both a and b"""

    # TODO
    first_sen = sent_tokenize(a, language='english')
    second_sen = sent_tokenize(b, language='english')
    first_sen_set = set(first_sen)
    second_sen_set = set(second_sen)
    our_sen_set = set(first_sen_set).intersection(second_sen_set)
    return our_sen_set


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # TODO
    alist, blist = [], []
    for i in range(len(a) - n + 1):
        alist.append(a[i:i+n])
    for i in range(len(b) - n + 1):
        blist.append(b[i:i+n])
    aset, bset = set(alist), set(blist)
    sub_str_set = set(aset).intersection(bset)
    return sub_str_set