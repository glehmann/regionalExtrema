#include "itkValuedRegionalMinimaImageFilter.h"
#include "itkRegionalMinimaImageFilter.h"
#include "itkValuedRegionalMaximaImageFilter.h"
#include "itkRegionalMaximaImageFilter.h"

int main(int, char * argv[])
{
  const int dim = 2;
  
  typedef unsigned char PType;
  typedef itk::Image< PType, dim > IType;

  typedef itk::ValuedRegionalMinimaImageFilter< IType, IType > VMinType;
  VMinType::Pointer vmin = VMinType::New();

  typedef itk::RegionalMinimaImageFilter< IType, IType > MinType;
  MinType::Pointer min = MinType::New();

  typedef itk::ValuedRegionalMaximaImageFilter< IType, IType > VMaxType;
  VMaxType::Pointer vmax = VMaxType::New();

  typedef itk::RegionalMaximaImageFilter< IType, IType > MaxType;
  MaxType::Pointer max = MaxType::New();

  try
    {
    vmin->Update();
    return EXIT_FAILURE;
    }
  catch (itk::ExceptionObject & e)
    {}
  
  try
    {
    min->Update();
    return EXIT_FAILURE;
    }
  catch (itk::ExceptionObject & e)
    {}
  
  try
    {
    vmax->Update();
    return EXIT_FAILURE;
    }
  catch (itk::ExceptionObject & e)
    {}
  

  try
    {
    max->Update();
    return EXIT_FAILURE;
    }
  catch (itk::ExceptionObject & e)
    {}
  
  return 0;
}

