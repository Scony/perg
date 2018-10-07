import os

import pytest


@pytest.fixture(scope="session")
def executable_path():
    my_dir = os.path.dirname(__file__)
    bin_dir = os.path.abspath('{}/../../bin'.format(my_dir)) # TODO: join
    return '{}/perg'.format(bin_dir) # TODO: join
