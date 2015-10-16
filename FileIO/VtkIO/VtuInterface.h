/**
 * \file
 * \author Lars Bilke
 * \date   2014-09-25
 * \brief  Implementation of the VtuInterface class.
 *
 * \copyright
 * Copyright (c) 2012-2015, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#ifndef VTUINTERFACE_H_
#define VTUINTERFACE_H_

#include <string>
#include <vtkXMLWriter.h>

namespace MeshLib {
	class Mesh;
}

namespace FileIO
{

/**
 * \brief Reads and writes VtkXMLUnstructuredGrid-files (vtu) to and from OGS data structures.
 * This class is currently not inherited from Writer because VTK will implement
 * writing to a string from 6.2 onwards.
 */
class VtuInterface
{
public:
	/// Provide the mesh to write and set if compression should be used.
	VtuInterface(const MeshLib::Mesh* mesh, int dataMode = vtkXMLWriter::Binary, bool compressed = false);
	~VtuInterface();

	/// Read an unstructured grid from a VTU file
	/// \return The converted mesh or a nullptr if reading failed
	static MeshLib::Mesh* readVTUFile(std::string const &file_name);

	/// Writes the given mesh to file.
	/// Note: a MPI_Comm type argument is needed.
	/// \return True on success, false on error
	bool writeToFile(std::string const &file_name);

	/// Writes the given mesh to vtu file.
	/// \param file_name      File name.
	/// \param num_partitions Number of partiions to be merged.
	/// \return True on success, false on error
	bool writeVTU(std::string const &file_name, const int num_partitions = 0);

private:
	const MeshLib::Mesh* _mesh;
	int _data_mode;
	bool _use_compressor;
};

}

#endif /* VTUINTERFACE_H_ */
