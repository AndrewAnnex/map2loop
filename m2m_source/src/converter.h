/******************************************************************************
* converter.h
*
* Author: Vitaliy Ogarko, vogarko@gmail.com
*******************************************************************************/

#ifndef converter_h
#define converter_h

#include <vector>
#include <map>
#include <string>

#include "clipper.hpp"
#include "bounding_box.h"
#include "converter_types.h"

using namespace ClipperLib;

namespace ConverterLib {

// Main class for map data analysis.
class Converter
{
public:
  //! Set the output data folder.
  void SetOutputFolder(const std::string &path);

  //! Set sill description (contains).
  void SetSillDescription(const std::string &_sill_descript);

  //! 1. Reads polygons or faults data, that are stored using OGC WKT (Well-known text) format.
  //! 2. Calculates bounding boxes for all objects read.
  void ReadData(const std::string &filename, const std::string& keyword,
                const std::map<std::string, std::string>& constNames,
                const std::vector<int>& idsToRead = std::vector<int>());

  //! Clips all data based on the given window.
  void ClipData(const AABB &window);

  // Finds contacts between every pair of polygons.
  // Returns the total contact length.
  double FindContacts(Contacts &contacts) const;

  //! Identify types of polygon contacts.
  void IdentifyPolygonContactTypes(Contacts &contacts, double angleEpsilon, double distanceEpsilon) const;

  //! Identify igneous unit contacts.
  void IdentifyIgneousUnitContacts(UnitContacts &unitContacts,
                                   const std::string IGNEOUS_STRING,
                                   const std::string VOLCANIC_STRING) const;

  //! Extract contacts with the given polygon.
  static void FilterContactsByPolygon(const Contacts &contacts, Contacts &contacts_filtered,
                                      int poly_id, int depth, int poly_last_id = - 1, bool last_call = true);

  //! Filter unit strat/fault contacts.
  static void FilterUnitStratFaultContacts(UnitContacts &contacts, ContactType contactType,
                                           double minFractionInMixedContact);

  //! Filter igneous unit contacts.
  static void FilterIgneousUnitContacts(UnitContacts &contacts);

  //! Build lists of units and groups.
  void BuildUnitsAndGroupsLists();

  //! Decompose mixed polygon contacts to fault-contacts and stratigraphic contacts.
  static void SplitMixedPolygonContacts(Contacts &contacts);

  //! Build a list of unit contacts.
  void BuildUnitContactsList(const Contacts &poly_contacts, UnitContacts &unit_contacts) const;

  //! Writes an SVG image with all polygons stored with windows displayed on top.
  //! add_objects = 1: add points,
  //! add_objects = 2: add faults.
  void WriteImage(const std::string &filename, const std::vector<AABB> &windows, int add_objects = 0,
                  const Contacts *contacts = 0) const;

  //! Returns a reference to units.
  const Units& GetUnits() const;

  //! Returns a reference to groups.
  const Groups& GetGroups() const;

  //! Returns a reference to polygons.
  const Objects& GetPolygons() const;

  //! Returns a reference to groups.
  const Objects& GetFaults() const;

  //! Return a bounding box for all polygons.
  AABB GetAllPolygonsAABB() const;

  //! Prints perimeter lengths, for testing.
  void PrintLengths(double contacts_length) const;

private:
  //! Output data folder.
  std::string path_output;

  //! Input data containers.
  Objects polygons_read, faults_read, points_read;

  //! Clipped data containers.
  Objects polygons, faults, points;

  //! List of all units.
  Units units;

  //! List of all unit groups.
  Groups groups;

  //! For testing purposes, various perimeter lengths.
  double m_window_length, m_units_length;

  std::string sill_descript;

  //! Calculates bounding boxes for all objects.
  static void CalculateBoundingBoxesObj(Objects &objects);

  //! Clip the data based on the given window.
  static Objects ClipDataObj(const Objects &objects, const AABB &window, bool closed_path);

  //! Assign unique id to contacts.
  static void AssignContactIds(Contacts &contacts);

  //! Building polygon from an array of integers. Used in tests only.
  static void MakePolygonFromInts(const cInt *ints, int size, Path &p, double scale = 1.0);
};

}

#endif