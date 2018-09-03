from hecate.hecate import Runner


def test_initial_screen(executable_path):
    with Runner(executable_path) as term:
        term.await_text("It works!")
        term.press("q")
