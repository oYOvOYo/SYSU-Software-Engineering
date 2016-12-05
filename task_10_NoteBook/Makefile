init:
	pip install -r requirements.txt
test:
	py.test tests
autopepe8:
	autopep8 --in-place tests/*
	autopep8 --in-place notebook/*
clean:
	rm -rf notebook/*.pyc
	rm -rf tests/*.pyc
	rm -rf tests/__pycache__
	rm -rf .cache
	rm -rf data/*