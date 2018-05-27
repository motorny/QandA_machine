# QandA_machine
![banner image](QuestionAnswerMachine-image.jpg)
## Введение. Цель проекта
Проект предназначен для демонстрации возможностей применения искусственных нейронных сетей в области обработки естественного языка. Пользователю предоставляется возможность задать произвольные вопросы. Приложение подберет максимально осмысленный ответ из набора предложенных фраз, который также может быть задан пользователем в виде входных данных, формат которых уточняется ниже. Благодаря этому приложение может использоваться для имитации диалога с известной личностью. Тестовый набор фраз поставляется вместе с приложением.
## Сравнение с аналогами
| Название продукта | Интерфейс | Веб-версия | Релевантность ответов | Использование пользовательского набора фраз | Открытый исходный код |
 | --------------- | :---: | :---: | :---: | :---: | :---: |
 | ["Спроси у Путина"](http://w-o-s.ru/article/12392) | **+** | **+** | **-** | **-** | **-** |
 | ["Famous person answering"](https://github.com/motorny/QandA_machine) | **+** | **-** | **+** | **+** | **+** |
## Требования к аппаратуре
Проект предполагается легковесным и не будет требовать каких-то высоких системных требований, тестирование производилось на нескольких компьютерах, компьютер с наименьшими техническими характеристиками обладал с примерно следующей спецификацией, однако для комфортной работы программы требуется меньгие системные требования:
* Процессор i5-750 
* ОЗУ: 2 ГБ
## Требования к программному обеспечению
* Windows 7 x32/x64, Windows 8, Windows 8.1, Windows 10
* Microsoft Visual C++ 2015 Redistributable (x64) - 14.0.2412 или  Microsoft Visual C++ 2015 Redistributable (x64) - 14.0.24215 в зависимости от разрядности операционной системы
## Средства разработки программного обеспечения
* Microsoft Visual Studio 2015 ver. 14.0.25425.01 Update 3
* QT ver. 5.7.0
* GitHub Desktop client ver. 1.0.13
* Cpp Check Code Analysis Tools ver. 1.82
* Doxygen ver 1.8.14
## Характеристики продукта
*Производительность* приложения достаточна для комфортной работы пользователя, так как время набора вопроса пользователем значительно превышает необходимое время для выдачи приложением ответа.
*Расход памяти* определяется объемом входных данных, без учета этого приложение расходует 10 кБ.
*Надежность* приложения позволяет пользователю получать осмысленные ответы на корректно заданные вопросы, а также сообщать об отсутсвтии релевантного ответа. *Рыночная ниша* - программное обеспечение обработки естественного языка на основе нейронных сетей.
## Формат входных данных
Пользователь вводит свой вопрос таким же образом как задавал бы его человеку в переписке. То есть интерфейс представляет пользователю поле для ввода своего вопроса. 
Поле для ввода текста вопроса пользователя предоставлено графическим интерфейсом, описание которого находится в соответсвующем разделе.
Так же имеется поле для ввода базы цитат на основе которой должы строиться ответы на вопросы пользователя, данные должны быть в формате `.txt` или `.csv.`.
## Формат выходных данных
В ответ получается фраза, полученная к качестве ответа на вопрос пользователя. То есть данные для пользователя видны через графический интерфейс, создается иллюзия диалога с имитируемым человеком.
## Установка продукта
### Использование поставляемых файлов проекта Visual Studio
Для использования данного варианта установки требуется расширение QT для IDE Visual Studio.

Необходимо открыть `QAMachine.sln`, находящийся в папке `build` и выполнить сборку стандартным для Visual Studio способом. Выбор между Юнит-тестами/основной программой осуществляется путем выбора "StartUp project" в контекстном меню соответсвующего проекта.

### Сборка проекта с помощью CMake
Сборка продукта из исходных кодов осуществляется с помощью CMake. Получить дистрибутив CMake можно на [официальном сайте](https://cmake.org/).
* Добавить в переменную окружения PATH путь к директории `bin` установленного дистрибутива QT, например `C:\Qt\5.7\msvc2015\bin"`
* Открыть текстовый файл по следующему пути относительно корневой директории проекта: `<some-prjoect-dir>/test/CMakeLists.txt` и отредактировать строчку
```
    set(CMAKE_PREFIX_PATH С:/Qt/5.7/msvc2015)
```
Изменив путь на верный путь к директории QT. Путь должен быть таков, чтобы `<этот-путь>/bin/qmake.exe` было бы верным путем.
>Пути к корневой директории проекта и к директории QT не должны содержать элементов с пробельными символами в названиях.
* Создать папку с произвольным названием в корневой директории проекта, рядом с папками `src`, `dataset`, например, с помощью командной строки:
```
    mkdir build
```
* Перейти в созданную папку и выполнить команду создания проекта
```
    cd build
    cmake -G "Visual Studio 14 2015" ../
```
Аргумент `"../"` указывает путь к корневую директорию проекта (содержащую файло `CMakeLists.txt`). Если на предыдущем пункте папка была создана в ином месте, необходимо заменить "../" на верный путь к корневой дирекотрии проекта, однако не гарантируется верный запуск приложения, вследсвие некорректности путей к файлам для обучения.
* Далее необходимо открыть `QAMachine.sln` и выполнить сборку стандартным для Visual Studio способом. Выбор между Юнит-тестами/основной программой осуществляется путем выбора "StartUp project" в контекстном меню соответсвующего проекта.

Также возможен запуск переносимой версии приложения, поставляемой в архиве `*.zip`.
### Сборка документации
Для сборки документации необходимо установить утилиту doxygen с [официального сайта](http://www.stack.nl/~dimitri/doxygen/download.html#srcbin), затем, в корневой директории проекта выолнить команду 
```
   doxygen doxygen_config.txt
```
### Статическая проверка кода
Для статической проверки кода утилитой cppcheck необходимо установить её с [офицального сайта](http://cppcheck.sourceforge.net/), убедиться, что путь к папке с установленной утилитой прописан в переменной среды PATH, а затем выполнить в корневой директории проекта команду
```
   cppcheck —inconclusive —enable=all -I src/core —suppress=missingIncludeSystem src
```

## Запуск продукта
Приложению в качестве единственного аргумента командной строки может быть передан путь к файлу с фразами для обучения. Если запускается переносная версия, то необходимо запустить исполняемый файл, лежащий в архиве.

Существует два дополнительных модификатора запуска, один из которых можно передать при запуске в качестве аргумента командной строки:
```
   --save
```
Данный модификатор помимо запуска приложения в нормальном режиме (т.е. с обучением по базе пар вопрос/ответ и последующим переходом к взаимодействию с пользователем) после обработки базы и составления словаря и проиндексированной базы вопросов происходит сохранение этих обработанных структур во временные файлы для дальнейшего ускорения запуска приложения в режиме, который будет описан далее.

Режим
```
   --load
```
не проводит обработку исходной базы пар вопрос/ответ, а загружает ранее уже обработанные предыдущим режимом словарь и индексированные вопросы из временных файлов. После этого приложение переходит в режим взаимодействия с пользователем.

При отсутсутвии модификаторв не выполняется ни сохранение, ни загрузка, а приложение обучается по исходной базе пар вопрос/ответ и переходит в режим взаимодействия с пользователем.

## Описание интерфейса пользователя
Интерфейс приложения максимально прост и интуитивен, пользователь вводит свой вопрос в предоставленное поле для текстового ввода данных. Поле для ввода текста вопроса пользователя:
![Interface for message input by user](user-interface-prototype.png)

Так же присутствует кнопка для вложения файла с цитатами, семанитика которого описана в разделе формат входных данный.
## Описание API библиотеки
Ядро приложение имеет обертку в виде C++ класса, API методами которого являются:
* Задать вопрос:
```c++
  void askQuestion(std::string question);
```
* Получить ответ:
```c++
  std::string askQuestion(void);
```
* Передать файл с цитатами для обучения:
```c++
  void setFileForLearing(std::File file);
```
## Детали реализации
На основе введенных пользователем слов проводится классификация вопроса, затем для данного вопроса подбирается наиболее подходящий ответ на основе натренированной нейронной сети на базе цитат того человека, которого надо имитировать в качестве собеседника. 
## Тестирование
Тестирование проводилось  использованием  инструмента [QTest](https://www.qt.io/). Тестировались все модули индивидуальными тестами, а так же происходило тестирование интеграции компонент программы между собой.
  
Классы тестов:
* Корректность обработки входных данных
* Корректность обучения нейронной сети
* Корректность подбора наиболее релевантного ответа 
## Ссылки и литература
Использованные программные средства средства:
* [QT ver 5.7.0](https://www.qt.io/)
* [electron.js](https://electronjs.org/)
* [Doxygen ver 1.8.14](http://www.stack.nl/~dimitri/doxygen/download.html#srcbin)
* [Cpp Check Code Analysis Tools ver. 1.82](http://cppcheck.sourceforge.net/)
* [Microsoft Visual Studio 2015 Community Edition](https://www.visualstudio.com/)
* [Desktop Github client](https://desktop.github.com/)

Использованные литература и статьи:
<ul>
<li>[1] <a href="http://snowball.tartarus.org/algorithms/porter/stemmer.html">Dr Porter, The Porter stemming algorithm</a>.</li>
  <li>[2] <a href="https://code.google.com/archive/p/word2vec/">Проект Word2Vec</a>.</li>

</ul>   
