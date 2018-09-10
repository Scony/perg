from hecate.hecate import Runner


def test_minibuffer_shows_unsupported_keystrokes(executable_path):
    with Runner(executable_path) as term:
        for c in 'abcklmxyz':
            term.press(c)
            term.await_text(c)
        term.press('q')
