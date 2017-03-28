
UNAME := $(shell uname)

COPT := -std=c++0x -g -Wall
LOPT := 

ifeq ($(UNAME), Linux)
# Pour Linux
LOPT := $(LOPT) -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_features2d -lopencv_calib3d -lopencv_video -lopencv_videoio
else ifeq ($(UNAME), MINGW32_NT-6.1)
# Pour Windows/Mingw 
# modifier en fonction de votre chemin d'installation OpenCV
OCVPATH = /c/downloads/ocv3/release/install
LOPT := $(LOPT) -L$(OCVPATH)/x86/mingw/lib -lopencv_core300 -lopencv_imgproc300 -lopencv_highgui300 -lopencv_video300 -lopencv_videoio300 -lopencv_features2d300 -lopencv_objdetect300 -lopencv_imgcodecs300 -lopencv_calib3d300
COPT := $(COPT) -I"$(OCVPATH)/include" -march=i486
else
LOPT := $(LOPT) -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_features2d -lopencv_calib3d
endif

EXEMPLES = ex-1-1 ex-1-2 ex-1-3 ex-2-1 ex-2-2 ex-2-3 ex-3 ex-4 ex-5
CIBLES := $(patsubst %,build/%.exe,$(EXEMPLES))

# Liste des exercices
all: check-dirs $(CIBLES)

check-dirs: 
	@test -d ./build || mkdir ./build

build/%.exe:  %.cc
	@echo "Construction $@..."
	@$(CXX) $< -o $@ $(COPT) $(LOPT)

clean:
	@echo "Netoyage du projet..."
	@rm -rf build
