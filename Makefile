
#
# Makefile
#
# notes
#  - specified MPI_main.o by hand since there's no header for it
#  - use implicit rules as much as you can
#

APPLICATION=ds

LIBS=-framework foundation -framework OpenGL -framework GLUT -framework CoreAudio

OBJS=MPI_main.o MPI_Point2D.o MPI_PolyLine.o MPI_Workspace.o \
	MPI_GUIRootWindow.o MPI_Audio.o MPI_Scheduler.o MPI_Application.o \
	MPI_GUICallbacks.o \
	MPI_DrawPolyLineVisitor.o MPI_BasicStroke.o MPI_AudioSynth.o \
	MPI_BoundingBox.o \
	MPI_PolyLinePoint.o MPI_PolyLinePointListIterator.o \
	MPI_AudioCallback.o \
	MPI_AudioWavetable.o \
	MPI_AudioWavetableSynth.o \
	MPI_OneSpaceElement.o MPI_OneSpace.o \
	MPI_IntersectionElement.o MPI_ParticleSpace.o \
	MPI_CollisionElementVisitor.o MPI_OneSpaceElementPos.o MPI_Framelist.o \
	MPI_PoweredElement.o MPI_ParticleStroke.o MPI_OneSpaceConstIterator.o \
	MPI_PolyLinePointDequeIterator.o MPI_ParticleFactory.o \
	MPI_DrawElementVisitor.o MPI_OneSpaceIterator.o \
	MPI_Segment.o MPI_IntersectionPolyLine.o \
	MPI_IntersectPolyLineVisitor.o \
	MPI_ParticleSegment.o \
	MPI_IsctWithSegmentVisitor.o MPI_IsctWithParticleSegmentVisitor.o \
	MPI_SegmentIntersectionVisitor.o MPI_RemovalSegment.o \
	MPI_IsctWithRemovalSegmentVisitor.o MPI_RemovalStroke.o \
	MPI_RemovePolyLineEvent.o MPI_AudioParticleSpace.o \
	MPI_AudioPlayheadStroke.o MPI_AudioParticleFactory.o MPI_Map.o \
	MPI_CanonicalTimeArclengthMap.o \
	MPI_PlayheadStroke.o MPI_FloatTrain.o MPI_FloatTrainConstIterator.o \
	MPI_TimeFloat.o MPI_TrainElement.o MPI_TrainElementFactory.o \
	MPI_TextLines.o MPI_CountPoweredElementsVisitor.o

STKOBJS=Stk.o RtAudio.o WvIn.o
OBJS+=$(STKOBJS)

FLAGS=-c -Wall
# uncomment to enable debugging info
#FLAGS+=-g
# uncomment to enable optimization
FLAGS+=-O3 -DNDEBUG

# flags for compiling STK files
STKFLAGS=-D__GXX__ -D__MACOSX_CORE__

# uncomment both of these to enable profiling
#PROFILINGFLAGS=-pg
#FLAGS+=$(PROFILINGFLAGS)

all: $(APPLICATION)

$(APPLICATION): $(OBJS)
	$(CXX) -o $@ $(PROFILINGFLAGS) $(OBJS) $(LIBS)

# FIXME this should actually take the .h dependencies into account
%.o : %.cpp %.h
	$(CXX) $(FLAGS) $<

$(STKOBJS): %.o: %.cpp %.h
	$(CXX) $(FLAGS) $(STKFLAGS) $<

MPI_main.o: MPI_main.cpp
	$(CXX) $(FLAGS) $<

clean:
	rm -f $(OBJS)

clobber: clean
	rm -f $(APPLICATION)

