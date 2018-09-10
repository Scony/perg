import pytest
from hecate.hecate import Runner


def test_initial_screen(executable_path):
    with Runner(executable_path) as term:
        term.await_text('It works!')
        term.press('q')


def test_initial_screen_with_file(executable_path):
    with Runner(executable_path, 'path_to_file') as term:
        term.await_text('It works!')
        term.await_text('path_to_file')
        term.press('q')


def test_initial_status_bar(executable_path):
    with Runner(executable_path) as term:
        term.await_text('It works!')
        term.await_text('-- dummy status --')
        term.press('q')


@pytest.mark.parametrize('help_opt', ['-h', '--help'])
def test_help_screen(executable_path, help_opt):
    with Runner(executable_path, help_opt) as term:
        term.await_text('Usage:')
