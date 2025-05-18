![](https://github.com/user-attachments/assets/3089cba8-f08f-4645-80d8-f14048731338)

## Описание

Данные программы представляют собой сервер и клиент, реализующие процесс игры "Угадай число"

## Как заставить работать:

1. **Клонировать репозиторий и перейти в корневой каталог:**
   ```bash
    git clone https://github.com/BodyBuilderChimp/pr4sem2
    cd pr4sem2
   ```
2. **Скомпиллировать файлы через любой доступный компилятор (например gcc):**
   ```bash
    gcc server.c -o server
    gcc client.c -o client
   ```
3. **Запуск: (запускать можно как на одном компьютере, так и на двух разных компьютерах, находящихся в одной локальной сети)**
   ```bash
   ./server 1337
   ./client 127.0.0.1 1337
   ```
4. **Наслаждаться великолепным игровым процессом:**
   ```bash
    Connected to server 127.0.0.1 on port 1337
    Enter message: 50
    Server: Lower!

    Enter message: 25
    Server: Lower!

    Enter message: 20
    Server: Lower!

    Enter message: 10
    Server: Lower!

    Enter message: 5
    Server: Higher!

    Enter message: 7
    Server: Higher!

    Enter message: 8
    Server: Higher!

    Enter message: 9
    Server: Correct!
   ```
## Примечания
- Сервер ведет лог подключений и отключений клиентов, а также ходов игры. Так же он автоматически отключает игрока как только он угадает число
- Убедитесь, что порт, который вы используете, не занят другими приложениями
