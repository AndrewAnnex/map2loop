#ROI
minlong=117 # should back calc from metre system\n",
maxlong=118
minlat=-23
maxlat=-22

step_out=0
inset=0

minx=500057
maxx=603028
miny=7455348
maxy=7567953

#CRS
src_crs = {'init': 'EPSG:4326'}  
dst_crs = {'init': 'EPSG:28350'} 

#PATH
mname='hams3'
geology_file='hams2_geol.shp'
fault_file='GEOS_GEOLOGY_LINEARSTRUCTURE_500K_GSD.shp'
structure_file='hams2_structure.shp'



#CODES
gcode='GROUP_'
dcode='DIP'
ddcode='DIP_DIR'
ccode='CODE'
ncode='NAME'
ocode='OBJECTID'
gicode='GEOPNT_ID'
r1code='ROCKTYPE1'
r2code='ROCKTYPE2'
tcode='TYPE'
fcode='FEATURE'
dscode='DESCRIPTN'
ucode='UNITNAME'
mincode='MIN_AGE_MA'
maxcode='MAX_AGE_MA'
sill_label='sill'
intrusive_label='intrusive'
fold_label='Fold axial trace'
fault_label='Fault'
bedding_label='Bed'

#MODEL_EXTENTS
model_base=-8200


#DECIMATION
orientation_decimate=0
contact_decimate=10
fault_decimate=5
fold_decimate=5


#INTERPOLATION
gridx=50
gridy=50
scheme='scipy_rbf'
dist_buffer=5
intrusion_mode=0 # 1 all instrusions exluded from basal contacts, 0 only sills

#ASSUMPTIONS
pluton_dip=45
pluton_form='saucers' #pluton_form='dontknow'  #saucers \_____/  pancakes /_____\   domes /‾‾‾‾‾\  dontknow ???
fault_dip=90

#PATHS

local_paths=False
test_data_path='../test_data3/'
graph_path=test_data_path+'graph/'
tmp_path=test_data_path+'tmp/'
data_path=test_data_path+'data/'
dtm_path=test_data_path+'dtm/'
output_path=test_data_path+'output/'
vtk_path=test_data_path+'vtk/'
m2m_cpp_path='../m2m_cpp/'

fault_file=data_path+'GEOS_GEOLOGY_LINEARSTRUCTURE_500K_GSD.shp'
structure_file=data_path+'hams2_structure.shp'
geology_file=data_path+'hams2_geol.shp'

fault_file_csv=fault_file.replace(".shp",".csv").replace("/data/","/tmp/")
structure_file_csv=structure_file.replace(".shp",".csv").replace("/data/","/tmp/")
geology_file_csv=geology_file.replace(".shp",".csv").replace("/data/","/tmp/")

strat_graph_file=test_data_path+'graph/graph_strat.gml'

dtm_file=dtm_path+mname+'_dtm.tif'
dtm_reproj_file=dtm_path+mname+'_dtm_rp.tif'

if(not os.path.isdir(tmp_path)):
   os.mkdir(tmp_path)
if(not os.path.isdir(output_path)):
   os.mkdir(output_path)
if(not os.path.isdir(dtm_path)):
   os.mkdir(dtm_path)
if(not os.path.isdir(dtm_path)):
   os.mkdir(dtm_path)
if(not os.path.isdir(vtk_path)):
   os.mkdir(vtk_path)

print('Default parameters loaded from m2l_config.py:')
with open('../test_data3/m2l_config.py', 'r') as myfile:
  data = myfile.read()
  print(data)
  myfile.close()
print('\nModify these parameters in the cell below')