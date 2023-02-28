# Тестовое задание №2 в компанию Страус 
Клиент-серверное приложение.

Для запуска требуется g++ и OpenGL библиотеки

    sudo apt update
    sudo apt install build-essential freeglut3-dev

Скачать исходный код
    
    git clone https://github.com/merdwed/straus_test_2

Сборка клиента
    
    cd straus_test_2/client
    make

---

## Запуск сервера:

    cd straus_test_2/server
    python3 server.py

Серверная часть имеет набор консольных команд, попробуйте **help**

---

## Запуск клиента

    cd straus_test_2/client
    ./client

Интерфейс для авторизации консольный, по умолчанию адрес сервера 127.0.0.1:15243 имя пользователя - user

Управление в игровом мире:
- **w a s d** - передвижение камеры относительно взгляда, **q e** - перемещение камеры вверх вниз
- **← → ↑ ↓** - вращение камеры


## Исходный текст задания
Исполнителю необходимо написать клиент-серверное приложение с следующим поведением.

Пользователь запускает приложение клиента, авторизируется на сервере и запускает игру.
В игре он управляет перемещением объекта в пространстве с помощью клавиатуры и мыши (не обязательно).
Телеметрия игры (текущее время, положение объекта - координаты и ориентация, нажатые клавиши) постоянно передаются на сервер в онлайн режиме.
Сервер хранит пользователей игры, телеметрию каждого запуска игры.

Условия на выбор исполнителя:
- функционал телеметрии является желательным, но не обязательным
- графическое приложение клиента использует GUI библиотеку (например Qt) или какой-нибудь (без ограничений) игровой движок
- объект находится в 2D или 3D пространстве
- приложение сервера может иметь Web интерфейс работы с хранилищем пользователей и телеметрии, но не является обязательным требованием

Обязательные требования:
- ОС Linux Ubuntu 22.04 (как на клиенте так и на сервере)
- приложение клиента на C++
- backend сервер на Python
- тип обмена данными между клиентом и сервером: Unicast

Исполнитель задания может использовать любые библиотеки, инструменты и подходы по своему желанию.
Исполнитель должен предоставить готовые сборки (или исходный код) приложения-клиента и приложения-сервера с инструкцией запуска для разворачивания на ОС Linux Ubuntu 22.04.