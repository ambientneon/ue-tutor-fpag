# First Person Adventure (Unreal Engine)
[English (README.md)](./README.md)

Учебный проект по официальному туториалу Epic  
**[Code a First-Person Adventure Game in Unreal Engine](https://dev.epicgames.com/documentation/unreal-engine/code-a-firstperson-adventure-game-in-unreal-engine?lang=en-US)**  
(Unreal Engine **5.8.x**).

Репозиторий повторяет гайд и дополняет его простым внутриигровым UI, настройками и локализацией.


## Что внутри
### Из туториала
- Геймплей first-person adventure по официальному гайду Epic
- Исходники проекта в `AdventureGame/`

### Дополнительно
- **Меню паузы (Tab)** — ставит игру на паузу и открывает меню
- **Настройки**
  - Язык интерфейса: **English** / **Русский**
  - Общее **качество графики** (scalability)
- **Локализуемые строки UI** (String Tables + Localization Dashboard / `.locres`)
- Оформление меню в духе **матового / frosted** UI (общий shell + виджеты контента)

### Релизы
- Крупные бинарники (**> 10 MB**) **не** хранятся в истории git
- Публикуются через **[assetout](https://github.com/ambientneon/assetout)** в **GitHub Releases**
- В тот же релиз добавлена **Shipping**-сборка игры для Windows (без отладочных файлов)


## Структура репозитория
```text
.
├── AdventureGame/     # Проект Unreal (код, контент, конфиги)
├── ue-build/          # Локальный вывод package (в git не коммитится)
├── README.md
├── README.ru.md
└── .gitignore
```

Точные пути/метаданные assetout см. в документации [assetout](https://github.com/ambientneon/assetout).


## Требования
- **Unreal Engine 5.8.x** (разработка на 5.8.2)
- Visual Studio 2022 (workload C++ game development, проект разработка на VCS 2026) под Windows
- Git
- [assetout](https://github.com/ambientneon/assetout) — загрузка крупных бинарников из Releases


## Клонирование и синхронизация бинарников
### 1. Клонировать репозиторий
```bash
git clone https://github.com/ambientneon/ue-tutor-fpag.git
cd ue-tutor-fpag
```

### 2. Синхронизация через assetout
Файлы больше ~10 MB лежат в **GitHub Releases**, не в дереве git.  
Установка и команды — в upstream:

**https://github.com/ambientneon/assetout**

Типичный поток (точные команды — в README assetout):

```bash
# установить assetout способом из документации upstream
# из корня репозитория:
assetout pull
```

После успешной синхронизации локально должны появиться бинарники/контент, ожидаемые проектом.

> Если нужно только **поиграть** в собранную игру — скачайте Shipping-архив из **Releases**, собирать из исходников не обязательно.


## Открыть и собрать из исходников
1. Синхронизировать бинарники через assetout (выше)
2. Открыть `AdventureGame/AdventureGame.uproject` (или имя вашего `.uproject`)
3. Дождаться сборки editor target
4. Запуск в редакторе; для проверки локализации лучше **Standalone Game**

### Сборка Shipping (кратко)
Для публичного билда использовалось:
- Скомпилированные культуры **en** и **ru-RU**
- Packaging: cultures **en**, **ru-RU**; internationalization включён
- Stage данных локализации (например `Localization/Game`)
- **Always Cook** папки String Tables (**не** полагаться только на Primary Asset для `UStringTable`)
- Конфигурация **Shipping**, без загрузки `.pdb` в релиз

Если в Shipping нет текстов UI — проверьте наличие `.locres` и String Tables в staged-сборке.


## Запуск релизной сборки
1. **GitHub → Releases**
2. Скачать Windows Shipping-архив
3. Распаковать и запустить `.exe`

Замечания:
- SmartScreen может предупреждать о **неподписанной** сборке
- Язык и графику можно сменить в настройках (Tab → Settings)


## Управление (общее)
| Ввод | Действие |
|------|----------|
| **Tab** | Пауза / главное меню |
| WASD + мышь | Движение / обзор (как в туториале) |
| UI меню | Настройки, подтверждение / отмена |

Точные бинды — в Enhanced Input проекта.


## Локализация
- Тексты UI — **String Tables** + пайплайн локализации UE
- Смена языка в рантайме через настройки (коды вроде `en`, `ru-RU`)
- В Shipping должны попасть cooked String Tables и staged `.locres`


## Обратная связь
Репозиторий в первую очередь **учебный**.  
Issues и предложения — через GitHub Issues.


## Лицензии
- Туториал и движок — условия **Epic Games** и Unreal Engine EULA
- [assetout](https://github.com/ambientneon/assetout) — лицензия того проекта


## Ссылки
- [Туториал Epic — First-Person Adventure](https://dev.epicgames.com/documentation/unreal-engine/code-a-firstperson-adventure-game-in-unreal-engine?lang=en-US)
- [assetout](https://github.com/ambientneon/assetout)
- [Документация Unreal Engine](https://dev.epicgames.com/documentation/unreal-engine/)
