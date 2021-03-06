/**
 * Copyright (C) 2014 Schneider-Electric
 *
 * This file is part of "Mind Compiler" is free software: you can redistribute 
 * it and/or modify it under the terms of the GNU Lesser General Public License 
 * as published by the Free Software Foundation, either version 3 of the 
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Contact: mind@ow2.org
 *
 * Authors: Stephane Seyvoz
 * Contributors: 
 */

package org.ow2.mind.adl.simple;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.objectweb.fractal.adl.ADLException;
import org.objectweb.fractal.adl.Definition;
import org.ow2.mind.adl.DefinitionCompiler;
import org.ow2.mind.adl.GraphCompiler;
import org.ow2.mind.adl.graph.ComponentGraph;
import org.ow2.mind.compilation.CompilationCommand;

import com.google.inject.Inject;

/**
 * Inspired by {@link org.ow2.mind.adl.BasicGraphCompiler}
 * @author Stephane Seyvoz
 *
 */
public class SimpleGraphCompiler implements GraphCompiler {

  @Inject
  protected DefinitionCompiler definitionCompilerItf;

  // ---------------------------------------------------------------------------
  // Implementation of the Visitor interface
  // ---------------------------------------------------------------------------

  public Collection<CompilationCommand> visit(final ComponentGraph graph,
      final Map<Object, Object> context) throws ADLException {
    final List<CompilationCommand> result = new ArrayList<CompilationCommand>();

    final List<Definition> definitionList = new ArrayList<Definition>();
    final Map<String, Collection<ComponentGraph>> instanceMap = new HashMap<String, Collection<ComponentGraph>>();

    // visit graph to build instanceMap and compile definitions
    visitGraph(graph, instanceMap, definitionList, result, context);
    
    // never fill result, we just want to generate content, not compile/link
    return result;
  }

  // ---------------------------------------------------------------------------
  // Utility methods
  // ---------------------------------------------------------------------------

  protected void visitGraph(final ComponentGraph graph,
      final Map<String, Collection<ComponentGraph>> instanceMap,
      final List<Definition> definitionList,
      final List<CompilationCommand> result, final Map<Object, Object> context)
      throws ADLException {

    Collection<ComponentGraph> instances = instanceMap.get(graph
        .getDefinition().getName());
    if (instances == null) {
      // new definition, compile it.
      result
          .addAll(definitionCompilerItf.visit(graph.getDefinition(), context));
      instances = new ArrayList<ComponentGraph>();
      instances.add(graph);
      instanceMap.put(graph.getDefinition().getName(), instances);
      definitionList.add(graph.getDefinition());
    } else {
      // definition already compiled, simply add instance.
      instances.add(graph);
    }

    for (final ComponentGraph subComp : graph.getSubComponents()) {
      // TODO handle shared components
      visitGraph(subComp, instanceMap, definitionList, result, context);
    }
  }
}
