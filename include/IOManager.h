/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOManager.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hilton <hilton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 01:37:21 by hilton            #+#    #+#             */
/*   Updated: 2018/10/30 01:37:21 by hilton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOMANAGER_H
#define IOMANAGER_H

// !5
// This class is going to be static class.
// A static class is a class that only includes static member functions
// Therefore , the class will not have a constructor and a destructor

# include "Includes.h"

namespace Gameengine {
	class IOManager {
	public:
		// !jump to IOManager.cpp
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};
}

#endif 