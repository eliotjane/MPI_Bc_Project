# MPI_Bc_Project

The project to measure the contribution of additional parton scattering to the production of the B_c meson

This work is based on the prediction of collegues published here:

The method for this analysis is outlined as follows:

Check out DaVinciDev_version46_r2

lb-dev DaVinci/v46r2 \
cd BrunelDev_v46r2 \
git lb-use DaVinci \
git lb-use Phys \
git lb-checkout Phys/v27r1

then add TupleToolPVInfo by Dr Tom Hadavizadeh from https://gitlab.cern.ch/thadaviz/bcmultiplicity/-/tree/master/DaVinciOptions/TupleTool. 

Integrate this new tool into DaVinci/v46r2 using:

make purge \
make \
make install 

(Note: Sometimes the TupleTool will not work. If the error "TupleToolPVTrackInfo:: get():: No valid data at 'Rec/Vertex/PrimaryVertices'   StatusCode=FAILURE" appears it can be solved by commenting out the "m_pv_location" and then also the "declareProperty" line relating to the PV. Replace these with:

declareProperty( "PVsLocation", m_pv_location = LHCb::RecVertexLocation::Primary, "PV location to be used." );\

which solves the issue.)

Now use the python options file davinci_Bc_data_pp.py (adapted from an options file provided by Dr Matt Durham) to select the B-decay channel.
