# Makefile - Plan Calendar
# @author Stefan Prokop <prokoste@fit.cvut.cz>

# Nastaveni kompilatoru a prepinacu
CXX=g++
CXXFlags=-Wall -pedantic -Wno-long-long -O0 -ggdb -g -c -std=c++11

# Vytvori binarni podobu souboru v korenoven adresari prace
compile: Insert.o Connector.o Select.o main.o globals.o RegistrationView.o AuthController.o TerminalListener.o User.o UserRepository.o EventHelper.o LifeStyle.o LifeStyleException.o MaxDateTimeException.o DuplicateEntryException.o Validation.o AuthView.o Update.o Export.o BaseView.o DefaultView.o BaseRepository.o EventRepository.o Event.o LifeStyleRepository.o EventController.o EventView.o Calendar.o CalendarRepository.o UserNotFoundException.o
	$(CXX) Connector.o AuthController.o Validation.o EventRepository.o Event.o TerminalListener.o User.o UserRepository.o Insert.o EventHelper.o LifeStyle.o Select.o AuthView.o MaxDateTimeException.o EventView.o BaseView.o DefaultView.o Calendar.o RegistrationView.o UserNotFoundException.o LifeStyleException.o LifeStyleRepository.o CalendarRepository.o Update.o Export.o EventController.o BaseRepository.o globals.o main.o -L/usr/lib -lmysqlclient -o prokoste

# Spusti vysledny program
run:
	./prokoste

# Vytvori veskere vystupy generovane ze zdrojoveho kodu
all: compile doc

# Vygeneruje dokumentaci ze zdrojovych kodu
doc: 
	cd src; doxygen dox_conf.txt

# Kompilace jednotlivych trid a zavislosti
BaseRepository.o: src/Model/Repository/BaseRepository.cpp src/Model/Repository/BaseRepository.h
	$(CXX) $(CXXFlags) src/Model/Repository/BaseRepository.cpp -o BaseRepository.o
Export.o: src/Model/Export.cpp src/Model/Export.h
	$(CXX) $(CXXFlags) src/Model/Export.cpp -o Export.o
Event.o: src/Model/Entity/Event.cpp src/Model/Entity/Event.h
	$(CXX) $(CXXFlags) src/Model/Entity/Event.cpp -o Event.o
EventRepository.o: src/Model/Repository/EventRepository.cpp src/Model/Repository/EventRepository.h
	$(CXX) $(CXXFlags) src/Model/Repository/EventRepository.cpp -o EventRepository.o
LifeStyleException.o: src/Service/Exception/LifeStyleException.cpp src/Service/Exception/LifeStyleException.h
	$(CXX) $(CXXFlags) src/Service/Exception/LifeStyleException.cpp -o LifeStyleException.o
LifeStyleRepository.o: src/Model/Repository/LifeStyleRepository.cpp src/Model/Repository/LifeStyleRepository.h
	$(CXX) $(CXXFlags) src/Model/Repository/LifeStyleRepository.cpp -o LifeStyleRepository.o
LifeStyle.o: src/Model/Entity/LifeStyle.cpp src/Model/Entity/LifeStyle.h
	$(CXX) $(CXXFlags) src/Model/Entity/LifeStyle.cpp -o LifeStyle.o
MaxDateTimeException.o: src/Service/Exception/MaxDateTimeException.cpp src/Service/Exception/MaxDateTimeException.h
	$(CXX) $(CXXFlags) src/Service/Exception/MaxDateTimeException.cpp -o MaxDateTimeException.o
EventHelper.o: src/Service/DI/EventHelper.cpp src/Service/DI/EventHelper.h
	$(CXX) $(CXXFlags) src/Service/DI/EventHelper.cpp -o EventHelper.o	
Validation.o: src/Service/DI/Validation.cpp src/Service/DI/Validation.h
	$(CXX) $(CXXFlags) src/Service/DI/Validation.cpp -o Validation.o
UserNotFoundException.o: src/Service/Exception/UserNotFoundException.cpp src/Service/Exception/UserNotFoundException.h
	$(CXX) $(CXXFlags) src/Service/Exception/UserNotFoundException.cpp -o UserNotFoundException.o
DuplicateEntryException.o: src/Service/Exception/DuplicateEntryException.cpp src/Service/Exception/DuplicateEntryException.h
	$(CXX) $(CXXFlags) src/Service/Exception/DuplicateEntryException.cpp -o DuplicateEntryException.o
Connector.o: src/Service/MySQL/Connector.cpp src/Service/MySQL/Connector.h
	$(CXX) $(CXXFlags) src/Service/MySQL/Connector.cpp -L/usr/lib -lmysqlclient -o Connector.o
Calendar.o: src/Model/Entity/Calendar.cpp src/Model/Entity/Calendar.h
	$(CXX) $(CXXFlags) src/Model/Entity/Calendar.cpp -o Calendar.o
CalendarRepository.o: src/Model/Repository/CalendarRepository.cpp src/Model/Repository/CalendarRepository.h
	$(CXX) $(CXXFlags) src/Model/Repository/CalendarRepository.cpp -o CalendarRepository.o
EventController.o: src/Controller/EventController.cpp src/Controller/EventController.h src/View/EventView.h
	$(CXX) $(CXXFlags) src/Controller/EventController.cpp -o EventController.o
AuthController.o: src/Controller/AuthController.cpp src/Controller/AuthController.h src/View/AuthView.h src/Model/Repository/UserRepository.h src/globals.h
	$(CXX) $(CXXFlags) src/Controller/AuthController.cpp -o AuthController.o
TerminalListener.o: src/Listener/TerminalListener.cpp src/Listener/TerminalListener.h
	$(CXX) $(CXXFlags) src/Listener/TerminalListener.cpp -o TerminalListener.o
User.o: src/Model/Entity/User.cpp src/Model/Entity/User.h
	$(CXX) $(CXXFlags) src/Model/Entity/User.cpp -o User.o
UserRepository.o: src/Model/Repository/UserRepository.cpp src/Model/Repository/BaseRepository.h src/Model/Repository/UserRepository.h
	$(CXX) $(CXXFlags) src/Model/Repository/UserRepository.cpp -o UserRepository.o
Insert.o: src/Service/MySQL/Insert.cpp src/Service/MySQL/Insert.h
	$(CXX) $(CXXFlags) src/Service/MySQL/Insert.cpp -L/usr/lib -lmysqlclient -o Insert.o
Update.o: src/Service/MySQL/Update.cpp src/Service/MySQL/Update.h
	$(CXX) $(CXXFlags) src/Service/MySQL/Update.cpp -L/usr/lib -lmysqlclient -o Update.o
Select.o: src/Service/MySQL/Select.cpp src/Service/MySQL/Select.h
	$(CXX) $(CXXFlags) src/Service/MySQL/Select.cpp -L/usr/lib -lmysqlclient -o Select.o
AuthView.o: src/View/AuthView.cpp src/View/AuthView.h
	$(CXX) $(CXXFlags) src/View/AuthView.cpp -o AuthView.o
RegistrationView.o: src/View/RegistrationView.cpp src/View/RegistrationView.h
	$(CXX) $(CXXFlags) src/View/RegistrationView.cpp -o RegistrationView.o
BaseView.o: src/View/BaseView.cpp src/View/BaseView.h
	$(CXX) $(CXXFlags) src/View/BaseView.cpp -o BaseView.o
DefaultView.o: src/View/DefaultView.cpp src/View/DefaultView.h
	$(CXX) $(CXXFlags) src/View/DefaultView.cpp -o DefaultView.o
EventView.o: src/View/EventView.cpp src/View/EventView.h src/Controller/EventController.h
	$(CXX) $(CXXFlags) src/View/EventView.cpp -o EventView.o
globals.o: src/globals.cpp src/globals.h
	$(CXX) $(CXXFlags) src/globals.cpp -o globals.o
main.o: src/main.cpp src/Model/Repository/UserRepository.h src/Listener/TerminalListener.h src/globals.h
	$(CXX) $(CXXFlags) src/main.cpp -o main.o

# Uvedeni adresare do puvodniho stavu pred spustenim make
clean:
	rm -rf *.o prokoste doc/
